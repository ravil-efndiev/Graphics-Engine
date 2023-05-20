#include "Renderer.hpp"
#include "Rendering/OpenGL/GLVertexArray.hpp"
#include "Rendering/OpenGL/GLShaderProgram.hpp"
#include "Rendering/OpenGL/GLTexture.hpp"
#include "OrthographicCamera.hpp"
#include "PerspectiveCamera.hpp"

namespace rvl
{
    glm::mat4 Renderer::_projview (1.0f);
    glm::vec3 Renderer::_clearColor;

    Ref<GLVertexArray> Renderer::_rectVao;
    Ref<GLVertexBuffer> Renderer::_rectPositionVbo;
    Ref<GLVertexBuffer> Renderer::_rectColorVbo;
    Ref<GLVertexBuffer> Renderer::_rectTexctureCoordsVbo;
    Ref<GLVertexBuffer> Renderer::_rectTextureIndexVbo;
    Ref<GLShaderProgram> Renderer::_textureShader;

    uint32_t Renderer::_rectIndiciesCount = 0;

    std::array<Ref<GLTexture>, 16> Renderer::_textureSlots;
    int Renderer::_textureSlotIndex = 1;

    std::vector<glm::vec3> Renderer::_rectPositionVBOData;
    std::vector<glm::vec4> Renderer::_rectColorVBOData;
    std::vector<glm::vec2> Renderer::_rectTexCoordsVBOData;
    std::vector<float> Renderer::_rectTexIndexVBOData;

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
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        _rectVao = NewRef<GLVertexArray>();

		_rectPositionVbo = NewRef<GLVertexBuffer>(_verticiesPerCall * sizeof(glm::vec3), 3);
		_rectColorVbo = NewRef<GLVertexBuffer>(_verticiesPerCall * sizeof(glm::vec4), 4);
        _rectTextureIndexVbo = NewRef<GLVertexBuffer>(_verticiesPerCall * sizeof(float), 1);
        _rectTexctureCoordsVbo = NewRef<GLVertexBuffer>(_verticiesPerCall * sizeof(glm::vec2), 2);

		_rectVao->AddVertexBuffer(_rectPositionVbo);
		_rectVao->AddVertexBuffer(_rectColorVbo);
		_rectVao->AddVertexBuffer(_rectTexctureCoordsVbo);
		_rectVao->AddVertexBuffer(_rectTextureIndexVbo);

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

		_textureShader = NewRef<GLShaderProgram>("assets/shaders/Texture.vert", "assets/shaders/Texture.frag");
		_textureShader->BindAttribute(0, "a_Position");
		_textureShader->BindAttribute(1, "a_Color");
		_textureShader->BindAttribute(2, "a_TexCoords");
		_textureShader->BindAttribute(3, "a_TexIndex");
		_textureShader->Link();

		_textureShader->Bind();

        int samples[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
        _textureShader->SetUniformIntArr("u_Textures", samples, 16);

        Ref<GLTexture> whiteTexture = NewRef<GLTexture>(1, 1);

        uint8_t whiteTexData[3] = {0xff, 0xff, 0xff};
        whiteTexture->SetData(whiteTexData, 3);

        _textureSlots[0] = whiteTexture; 
    }

    void Renderer::Shutdown()
    {
    }

    void Renderer::BeginContext(OrthographicCamera& camera, float viewportWidth, float viewportHeight)
    {
        _projview = camera.GetProjectionMatrix(viewportWidth, viewportHeight) * camera.GetViewMatrix();

        _textureShader->Bind();
        _textureShader->SetUniformMat4("u_Projview", _projview);

        BeginBatch();
    }

    void Renderer::EndContext()
    {
		_rectPositionVbo->SetData(_rectPositionVBOData.data(), _rectPositionVBOData.size() * sizeof(glm::vec3));

		_rectColorVbo->SetData(_rectColorVBOData.data(), _rectColorVBOData.size() * sizeof(glm::vec4));

        _rectTexctureCoordsVbo->SetData(_rectTexCoordsVBOData.data(), _rectTexCoordsVBOData.size() * sizeof(glm::vec2));

        _rectTextureIndexVbo->SetData(_rectTexIndexVBOData.data(), _rectTexIndexVBOData.size() * sizeof(float));        

        _textureShader->Bind();

        for (int i = 0; i < _textureSlotIndex; i++)
        {
            _textureSlots[i]->Bind(i);
        }

		DrawIndicies(_rectVao, _rectIndiciesCount);

        Stats.DrawCalls++;
    }

    void Renderer::SubmitGeometry(GLVertexArray& vertexArray, GLShaderProgram& shader)
    {
        shader.Bind();
        shader.SetUniformMat4("projview", _projview);
        DrawIndicies(vertexArray);
        shader.Unbind();
    }

    void Renderer::DrawRect(const Transform& transform, const glm::vec4& color)
    {
        if (_rectIndiciesCount >= _indiciesPerCall)
            FlushAndReset();

        const glm::vec2 coords[4] = { {0.f, 0.f}, {1.f, 0.f}, {1.f, 1.f}, {0.f, 1.f} };

        glm::mat4 transformMat = transform.GetMatrix();
        
        for (int i = 0; i < 4; i++)
        {
            _rectPositionVBOData.push_back(transformMat * _rectVertexPositions[i]);
            _rectTexCoordsVBOData.push_back(coords[i]);
            _rectColorVBOData.push_back(color);
            _rectTexIndexVBOData.push_back(0.f);
        }

		_rectIndiciesCount += 6;

        Stats.RectCount++;
        Stats.VerticiesCount += 4;
        Stats.IndiciesCount += 6;
    }

    void Renderer::DrawRect(const Transform& transform, const Ref<GLTexture>& texture)
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
            _rectPositionVBOData.push_back(transformMat * _rectVertexPositions[i]);
            _rectTexCoordsVBOData.push_back(coords[i]);
            _rectColorVBOData.push_back({1.f, 1.f, 1.f, 1.f});
            _rectTexIndexVBOData.push_back(textureIndex);
        }

		_rectIndiciesCount += 6;        

        Stats.RectCount++;
        Stats.VerticiesCount += 4;
        Stats.IndiciesCount += 6;
    }

    void Renderer::DrawRect(const Transform& transform, const Ref<SubTexture>& subtexture)
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
            _rectPositionVBOData.push_back(transformMat * _rectVertexPositions[i]);
            _rectTexCoordsVBOData.push_back(coords[i]);
            _rectColorVBOData.push_back({1.f, 1.f, 1.f, 1.f});
            _rectTexIndexVBOData.push_back(textureIndex);
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

    inline void Renderer::DrawIndicies(const Ref<GLVertexArray>& vertexArray, int indexCount)
    {
        int count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetIndiciesCount();
        vertexArray->Bind();
        vertexArray->BindIndexBuffer();
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
        vertexArray->UnbindIndexBuffer();
        vertexArray->Unbind();
    }

    inline void Renderer::DrawIndicies(GLVertexArray& vertexArray, int indexCount)
    {
        int count = indexCount ? indexCount : vertexArray.GetIndexBuffer()->GetIndiciesCount();
        vertexArray.Bind();
        vertexArray.BindIndexBuffer();
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
        vertexArray.UnbindIndexBuffer();
        vertexArray.Unbind();
    }

    void Renderer::BeginBatch()
    {
        _rectIndiciesCount = 0;

        _rectPositionVBOData.clear();
        _rectColorVBOData.clear();
        _rectTexCoordsVBOData.clear();
        _rectTexIndexVBOData.clear();

        _textureSlotIndex = 1; 
    }

    void Renderer::FlushAndReset()
    {
        EndContext();
        BeginBatch();
    }

    void Renderer::SetClearColor(const glm::vec3& clearColor)
    {
        _clearColor = clearColor;
    }

    void Renderer::Clear()
    {
        glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::GetViewport(int rViewport[2])
    {
        int viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);

        rViewport[0] = viewport[2];
        rViewport[1] = viewport[3];
    }

    glm::vec2 Renderer::ConvertToWorldCoords(double x, double y)
    {
        int viewport[2];
        GetViewport(viewport);
        glm::vec4 vec4viewport (0, 0, viewport[0], viewport[1]);
        glm::vec3 pos (x, viewport[1] - y, 0);

        glm::vec3 worldCoords = glm::unProject(pos, glm::mat4(1.0f), _projview, vec4viewport);
        return glm::vec2(worldCoords.x, worldCoords.y);
    }
}
