#include "Renderer2D.hpp"

#include <Rvlpch.hpp>
#include <Rvlglpch.hpp>

#include <Rendering/OpenGL/GLVertexArray.hpp>
#include <Rendering/OpenGL/GLBuffer.hpp>
#include <Rendering/OpenGL/GLTexture.hpp>
#include <Rendering/OpenGL/GLShaderProgram.hpp>

#include <glm/gtc/matrix_transform.hpp>

namespace rvl
{
	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		// TODO: texid
	};


	struct Renderer2DData
	{
		const uint32_t MaxQuads = 10000;
		const uint32_t MaxVertices = MaxQuads * 4;
		const uint32_t MaxIndices = MaxQuads * 6;

		Ref<GLVertexArray> QuadVertexArray;
		Ref<GLVertexBuffer> QuadVertexBuffer;
		Ref<GLShaderProgram> TextureShader;
		Ref<GLTexture> WhiteTexture;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;
	};

	static Renderer2DData s_Data;

	void Renderer2D::Init()
	{
		s_Data.QuadVertexArray = CreateRef<GLVertexArray>();

		s_Data.QuadVertexBuffer = CreateRef<GLVertexBuffer>(s_Data.MaxVertices * sizeof(QuadVertex));

		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];

		std::vector<uint32_t> quadIndices = std::vector<uint32_t>(s_Data.MaxIndices, 0);

		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data.MaxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		Ref<GLIndexBuffer> quadIB = CreateRef<GLIndexBuffer>(quadIndices);
		s_Data.QuadVertexArray->AddIndexBuffer(quadIB);

		s_Data.WhiteTexture = CreateRef<GLTexture>(1, 1);
		uint8_t whiteTextureData = (uint8_t)0xffffffff;
		s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint8_t));

		s_Data.TextureShader = CreateRef<GLShaderProgram>("assets/shaders/Texture.vert", "assets/shaders/Texture.frag");
		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetUniformInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
	}

    inline void Renderer2D::DrawIndicies(const Ref<GLVertexArray>& vertexArray, int indexCount)
    {
        int count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetIndiciesCount();
        vertexArray->Bind();
        vertexArray->BindIndexBuffer();
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
        vertexArray->UnbindIndexBuffer();
        vertexArray->Unbind();
    }

	void Renderer2D::BeginScene(OrthographicCamera& camera)
	{
        int viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);

		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetUniformMat4("u_Projview", camera.GetProjectionMatrix(viewport[2], viewport[3]) * camera.GetViewMatrix());

		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
	}

	void Renderer2D::EndScene()
	{

        float verticies[7 * 4] =
        {
            -0.5f, -0.5f, 0.0f, 1.f, 1.f, 1.f, 1.f,
            0.5f, -0.5f, 0.f, 1.f, 1.f, 1.f, 1.f,
            0.5f, 0.5f, 0.f, 1.f, 1.f, 1.f, 1.f,
            -0.5f, 0.5f, 0.f, 1.f, 1.f, 1.f, 1.f,
        };

		uint32_t dataSize = (uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase;
		s_Data.QuadVertexBuffer->SetData(verticies, 7 * 4 * sizeof(float));

		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

		Flush();
	}

	void Renderer2D::Flush()
	{
		DrawIndicies(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{

		s_Data.QuadVertexBufferPtr->Position = position;
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { position.x + size.x, position.y, 0.0f };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { position.x + size.x, position.y + size.y, 0.0f };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		s_Data.QuadVertexBufferPtr++;


		s_Data.QuadVertexBufferPtr->Position = { position.x, position.y + size.y, 0.0f };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		s_Data.QuadVertexBufferPtr++;

		uint32_t dataSize = (uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase;

        for (int i = 0; i < dataSize; i++)
        {
            RVL_LOG(s_Data.QuadVertexBufferBase[i].Color.x);
        }

		s_Data.QuadIndexCount += 6;

		/*s_Data.TextureShader->SetFloat("u_TilingFactor", 1.0f);
		s_Data.WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data.TextureShader->SetMat4("u_Transform", transform);
		s_Data.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.QuadVertexArray);*/
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<GLTexture>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		//DrawQuad({ position.x, position.y, 0.0f }, size, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<GLTexture>& texture, float tilingFactor, const glm::vec4& tintColor)
	{

		/*s_Data.TextureShader->SetUniformVec4("u_Color", tintColor);
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data.TextureShader->SetUniformMat4("u_Transform", transform);

		s_Data.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.QuadVertexArray);
        */
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		//DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{

		/*s_Data.TextureShader->SetUniformVec4("u_Color", color);
		s_Data.WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data.TextureShader->SetUniformMat4("u_Transform", transform);
		s_Data.QuadVertexArray->Bind();
		DrawIs_Data.QuadVertexArray);*/
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<GLTexture>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		//DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<GLTexture>& texture, float tilingFactor, const glm::vec4& tintColor)
	{

		/*s_Data.TextureShader->SetFloat4("u_Color", tintColor);
		s_Data.TextureShader->SetFloat("u_TilingFactor", tilingFactor);
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data.TextureShader->SetMat4("u_Transform", transform);

		s_Data.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.QuadVertexArray);*/
	}

}
