#include "Renderer.hpp"
#include "Rendering/OpenGL/GLVertexArray.hpp"
#include "Rendering/OpenGL/GLShaderProgram.hpp"
#include "Rendering/OpenGL/GLTexture.hpp"
#include "OrthographicCamera.hpp"
#include "PerspectiveCamera.hpp"

namespace Rvl
{
    struct RectVertex 
    {
        glm::vec3 Position;
        glm::vec4 Color;
        glm::vec2 TexCoord;
        float TexIndex;
    };

    glm::mat4 Renderer::_projview (1.0f);

    Ref<GLVertexArray> Renderer::_rectVao;
    Ref<GLVertexBuffer> Renderer::_rectVbo;
    Ref<GLShaderProgram> Renderer::_textureShader;

    uint32_t Renderer::_rectIndiciesCount = 0;

    std::array<Ref<GLTexture>, 16> Renderer::_textureSlots;
    int Renderer::_textureSlotIndex = 1;

    static std::vector<RectVertex> _rectVBOData;

    const glm::vec4 Renderer::_rectVertexPositions[4] = 
    {
        {-0.5f, -0.5f, 0.f, 1.f},
        {0.5f, -0.5f, 0.f, 1.f},
        {0.5f, 0.5f, 0.f, 1.f},
        {-0.5f, 0.5f, 0.f, 1.f},
    };

    static Renderer::Statistics Stats; 

    void Renderer::Init()
    {        
        _rectVao = NewRef<GLVertexArray>();

        _rectVbo = NewRef<GLVertexBuffer>(_verticiesPerCall * sizeof(RectVertex), 1);
        _rectVbo->SetLayout({
            { ElementType::Vec3, 0, sizeof(RectVertex), false },
            { ElementType::Vec4, offsetof(RectVertex, Color), sizeof(RectVertex), false },
            { ElementType::Vec2, offsetof(RectVertex, TexCoord), sizeof(RectVertex), false },
            { ElementType::Float, offsetof(RectVertex, TexIndex), sizeof(RectVertex), false },
        });


        _rectVao->SetSingleVertexBuffer(_rectVbo);

		std::vector<uint32_t> rectIndexData = std::vector<uint32_t>(_indiciesPerCall, 0);

		uint32_t offset = 0;
		for (uint32_t i = 0; i < _indiciesPerCall; i += 6)
		{
			rectIndexData[i + 0] = offset + 0;
			rectIndexData[i + 1] = offset + 1;
			rectIndexData[i + 2] = offset + 2;

			rectIndexData[i + 3] = offset + 2;
			rectIndexData[i + 4] = offset + 3;
			rectIndexData[i + 5] = offset + 0;

			offset += 4;
		}

		Ref<GLIndexBuffer> quadIB = NewRef<GLIndexBuffer>(rectIndexData);
		_rectVao->AddIndexBuffer(quadIB);

		_textureShader = NewRef<GLShaderProgram>("standart_assets/shaders/Texture.vert", "standart_assets/shaders/Texture.frag");

		_textureShader->Bind();
        int samples[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
        _textureShader->SetUniformIntArr("u_Textures", samples, 16);

        Ref<GLTexture> whiteTexture = NewRef<GLTexture>(1, 1);

        uint8_t whiteTexData[3] = {0xff, 0xff, 0xff};
        whiteTexture->SetData(whiteTexData, 3);

		_textureShader->Unbind();
        _textureSlots[0] = whiteTexture; 
    }

    void Renderer::Shutdown()
    {
    }

    void Renderer::BeginContext(const Ref<Camera>& camera, float viewportWidth, float viewportHeight)
    {
        _projview = camera->GetProjectionMatrix(viewportWidth, viewportHeight) * camera->GetViewMatrix();

        BeginBatch();
    }

    void Renderer::EndContext()
    {
        if (!_rectVBOData.empty())
        {
            _rectVbo->SetData(_rectVBOData.data(), _rectVBOData.size() * sizeof(RectVertex));

            _textureShader->Bind();
            _textureShader->SetUniformMat4("u_Projview", _projview);

            for (int i = 0; i < _textureSlotIndex; i++)
            {
                _textureSlots[i]->Bind(i);
            }

            GLTexture::ActivateTexture(0);
            RenderCommand::DrawIndicies(_rectVao, _rectIndiciesCount);

            _textureShader->Unbind();

            Stats.DrawCalls++;
        }
    }

    void Renderer::DrawRect(const Transform& transform, const glm::vec4& color)
    {
        if (_rectIndiciesCount >= _indiciesPerCall)
            FlushAndReset();

        const glm::vec2 coords[4] = { {0.f, 0.f}, {1.f, 0.f}, {1.f, 1.f}, {0.f, 1.f} };

        glm::mat4 transformMat = transform.GetMatrix();
        
        for (int i = 0; i < 4; i++)
        {
            _rectVBOData.push_back({
                transformMat * _rectVertexPositions[i],
                color,
                coords[i],
                0.f
            });
        }

		_rectIndiciesCount += 6;

        Stats.RectCount++;
        Stats.VerticiesCount += 4;
        Stats.IndiciesCount += 6;
    }

    void Renderer::DrawRect(const Transform& transform, const Ref<GLTexture>& texture, const glm::vec4& tintColor)
    {
        if (_rectIndiciesCount >= _indiciesPerCall)
            FlushAndReset();

        float textureIndex = 0.f;

        const glm::vec2 coords[4] = { {0.f, 0.f}, {1.f, 0.f}, {1.f, 1.f}, {0.f, 1.f} };


        for (int i = 1; i < _textureSlotIndex; i++)
        {
            if (*_textureSlots[i] == *texture)
            {
                textureIndex = i;                
                break;
            }
        }

        if (!textureIndex)
        {
            textureIndex = _textureSlotIndex;
            _textureSlots[_textureSlotIndex] = texture;
            _textureSlotIndex++;
        }

        glm::mat4 transformMat = transform.GetMatrix();

        for (int i = 0; i < 4; i++)
        {
            _rectVBOData.push_back({
                transformMat * _rectVertexPositions[i],
                tintColor,
                coords[i],
                textureIndex
            });
        }

		_rectIndiciesCount += 6;        

        Stats.RectCount++;
        Stats.VerticiesCount += 4;
        Stats.IndiciesCount += 6;
    }

    void Renderer::DrawRect(const Transform& transform, const Ref<SubTexture>& subtexture, const glm::vec4& tintColor)
    {
        if (_rectIndiciesCount >= _indiciesPerCall)
            FlushAndReset();

        const Ref<GLTexture> texture = subtexture->GetTexture();
        const glm::vec2* coords = subtexture->GetCoords();

        float textureIndex = 0.f;

        for (int i = 1; i < _textureSlotIndex; i++)
        {
            if (*_textureSlots[i] == *texture)
            {
                textureIndex = i;                
                break;
            }
        }

        if (textureIndex == 0.f)
        {
            textureIndex = _textureSlotIndex;
            _textureSlots[_textureSlotIndex] = texture;
            _textureSlotIndex++;
        }

        glm::mat4 transformMat = transform.GetMatrix();

        for (int i = 0; i < 4; i++)
        {
            _rectVBOData.push_back({
                transformMat * _rectVertexPositions[i],
                tintColor,
                coords[i],
                textureIndex
            });
        }

		_rectIndiciesCount += 6;        

        Stats.RectCount++;
        Stats.VerticiesCount += 4;
        Stats.IndiciesCount += 6;
    }

    Renderer::Statistics Renderer::GetStats()
    {
        return Stats;
    }

    void Renderer::ResetStats()
    {
        Stats.DrawCalls = 0;
        Stats.RectCount = 0;
        Stats.VerticiesCount = 0;
        Stats.IndiciesCount = 0;
    }

    void Renderer::BeginBatch()
    {
        _rectIndiciesCount = 0;

        _rectVBOData.clear();

        _textureSlotIndex = 1; 
    }

    void Renderer::FlushAndReset()
    {
        EndContext();
        BeginBatch();
    }

    glm::vec2 Renderer::ConvertToWorldCoords(double x, double y)
    {
        glm::vec2 viewport = RenderCommand::GetViewport();

        glm::vec4 vec4viewport (0, 0, viewport.x, viewport.y);
        glm::vec3 pos (x, viewport.x - y, 0);

        glm::vec3 worldCoords = glm::unProject(pos, glm::mat4(1.0f), _projview, vec4viewport);
        return glm::vec2(worldCoords.x, worldCoords.y);
    }
    
    glm::vec2 Renderer::ConvertToWorldCoords(double x, double y, const glm::vec2& pos)
    {
        glm::vec2 viewport = RenderCommand::GetViewport();

        glm::vec4 vec4viewport (pos.x, pos.y, viewport.x, viewport.y);
        glm::vec3 posi (x, viewport.x - y, 0);

        glm::vec3 worldCoords = glm::unProject(posi, glm::mat4(1.0f), _projview, vec4viewport);
        return glm::vec2(worldCoords.x, worldCoords.y);
    }
}
