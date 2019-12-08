#include "hzpch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

namespace Hazel {

	struct Renderer2DStorage {
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> FlatColorShader;

	};

	static Renderer2DStorage *s_Data;

	void Renderer2D::Init() {
		s_Data = new Renderer2DStorage;
		s_Data->QuadVertexArray = VertexArray::Create();

		float vertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
		};

		Hazel::Ref<Hazel::VertexBuffer> vertexBuffer(Hazel::VertexBuffer::Create(vertices, sizeof(vertices)));

		uint32_t indices[3 * 2] = {
			0, 1, 2,
			0, 2, 3
		};
		Hazel::Ref<Hazel::IndexBuffer> indexBuffer(Hazel::IndexBuffer::Create(indices, 3 * 4));
		s_Data->QuadVertexArray->SetIndexBuffer(indexBuffer);

		Hazel::BufferLayout layout({
			{Hazel::ShaderDataType::Float3, "a_Position"}
			});
		vertexBuffer->SetLayout(layout);
		s_Data->QuadVertexArray->AddVertexBuffer(vertexBuffer);


		s_Data->FlatColorShader = Hazel::Shader::Create("assets/shaders/FlatColor.glsl");
	}
	void Renderer2D::Shutdown() {
		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera) {
		s_Data->FlatColorShader->Bind();
		s_Data->FlatColorShader->SetMat4("u_ViewProjection", camera.GetViewProjection());
		s_Data->FlatColorShader->SetMat4("u_Transform", glm::mat4(1.f));
	}
	void Renderer2D::EndScene() {

	}

	void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color) {
		DrawQuad({pos.x, pos.y, 0.f }, size, color);
	}
	void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color) {
		s_Data->FlatColorShader->Bind();
		s_Data->FlatColorShader->SetFloat4("u_Color", color);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}
}