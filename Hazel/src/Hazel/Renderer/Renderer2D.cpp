#include "hzpch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

namespace Hazel {

	struct Renderer2DStorage {
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;
	};

	static Renderer2DStorage *s_Data;

	void Renderer2D::Init() {
		HZ_PROFILE_FUNCTION();

		s_Data = new Renderer2DStorage;
		s_Data->QuadVertexArray = VertexArray::Create();
		s_Data->TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		s_Data->WhiteTexture = Texture2D::Create(1, 1);
		s_Data->WhiteTexture->Bind();
		uint32_t data = 0xffffffff;
		s_Data->WhiteTexture->SetData(&data, sizeof(uint32_t));

		float vertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Hazel::Ref<Hazel::VertexBuffer> vertexBuffer(Hazel::VertexBuffer::Create(vertices, sizeof(vertices)));

		uint32_t indices[3 * 2] = {
			0, 1, 2,
			0, 2, 3
		};
		Hazel::Ref<Hazel::IndexBuffer> indexBuffer(Hazel::IndexBuffer::Create(indices, 3 * 4));
		s_Data->QuadVertexArray->SetIndexBuffer(indexBuffer);

		Hazel::BufferLayout layout({
			{Hazel::ShaderDataType::Float3, "a_Position"},
			{Hazel::ShaderDataType::Float2, "a_TexCoord"},
			});
		vertexBuffer->SetLayout(layout);
		s_Data->QuadVertexArray->AddVertexBuffer(vertexBuffer);

		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetInt("u_Texture", 0);
	}
	void Renderer2D::Shutdown() {
		HZ_PROFILE_FUNCTION();

		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera) {
		HZ_PROFILE_FUNCTION();

		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjection());
	}
	void Renderer2D::EndScene() {
		HZ_PROFILE_FUNCTION();

	}

	void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color) {
		DrawQuad({pos.x, pos.y, 0.f }, size, color);
	}
	void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color) {
		HZ_PROFILE_FUNCTION();

		s_Data->WhiteTexture->Bind();
		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetFloat4("u_Color", color);

		glm::mat4 transform = glm::translate(pos) * glm::scale(glm::vec3{size.x, size.y, 1.f});
		s_Data->TextureShader->SetMat4("u_Transform", transform);
		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const Ref<Texture>& texture) {
		DrawQuad({ pos.x, pos.y, 0.f }, size, texture);
	}

	void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const Ref<Texture>& texture) {
		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetFloat4("u_Color", glm::vec4{ 1.f });
		texture->Bind();

		glm::mat4 transform = glm::translate(pos) * glm::scale(glm::vec3{ size.x, size.y, 1.f });
		s_Data->TextureShader->SetMat4("u_Transform", transform);
		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}
}