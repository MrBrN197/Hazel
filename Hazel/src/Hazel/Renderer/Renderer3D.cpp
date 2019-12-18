#include "hzpch.h"
#include "Renderer3D.h"
#include "RenderCommand.h"
#include "Shader.h"
#include "Texture.h"

namespace Hazel {
	
	struct Renderer3DStorage {
		Ref<Shader> shader;
		Ref<Texture2D> defaultTexture;
		Ref<VertexArray> vertexArray;
		Ref<VertexArray> floorVertexArray;
		Ref<Texture2D> checkeredTexture;
	};

	static Renderer3DStorage* s_Data3D;

	void Renderer3D::Init() {
		HZ_PROFILE_FUNCTION();

		s_Data3D = new Renderer3DStorage;
		s_Data3D->shader = Shader::Create("assets/shaders/Texture.glsl");
		s_Data3D->defaultTexture = Texture2D::Create(1, 1);
		s_Data3D->checkeredTexture = Texture2D::Create("assets/textures/Checkerboard.png");
		s_Data3D->shader->SetInt("u_Texture", 0);

		uint32_t data = 0xffffffff;
		s_Data3D->defaultTexture->SetData(&data, sizeof(uint32_t));

		s_Data3D->vertexArray = VertexArray::Create();
		s_Data3D->vertexArray->Bind();
		uint32_t indices[36] = {
			0, 1, 2, 0, 2, 3, // Front
			4, 5, 6, 4, 6, 7, // Back
			4, 0, 3, 4, 3, 7, // Left
			1, 5, 6, 1, 6, 2, // Right
			3, 2, 6, 3, 6, 7, // Top
			1, 0, 4, 1, 4, 5  // Bottom
		};
		float vertices[8 * 5] = {
			-0.5f, -0.5f, 0.5f, 0.f, 0.f,
			 0.5f, -0.5f, 0.5f, 1.f, 0.f,
			 0.5f,  0.5f, 0.5f, 1.f, 1.f,
			-0.5f,  0.5f, 0.5f, 0.f, 1.f,
			-0.5f, -0.5f,-0.5f, 0.f, 0.f,
			 0.5f, -0.5f,-0.5f, 1.f, 0.f,
			 0.5f,  0.5f,-0.5f, 1.f, 1.f,
			-0.5f,  0.5f,-0.5f, 0.f, 1.f
		};
		auto indexBuffer = IndexBuffer::Create(indices, 36);
		auto vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
		vertexBuffer->SetLayout({
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float2, "a_TexCoord"},
		});

		s_Data3D->vertexArray->SetIndexBuffer(indexBuffer);
		s_Data3D->vertexArray->AddVertexBuffer(vertexBuffer);


		// FLOOR

		s_Data3D->floorVertexArray = VertexArray::Create();
		s_Data3D->floorVertexArray->Bind();
		uint32_t floorIndices[6] = { 0, 1, 2, 0, 2, 3};
		float floorVertices[4 * 5] = {
			-20.5f, -0.5f,  20.5f,  0.f, 0.f,
			 20.5f, -0.5f,  20.5f,  1.f, 0.f,
			 20.5f, -0.5f, -20.5f, 1.f, 1.f,
			-20.5f, -0.5f, -20.5f, 0.f, 1.f
		};
		auto indexBufferFloor = IndexBuffer::Create(floorIndices, 6);
		auto vertexBufferFloor = VertexBuffer::Create(floorVertices, sizeof(floorVertices));
		vertexBufferFloor->SetLayout({
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float2, "a_TexCoord"},
		});

		s_Data3D->floorVertexArray->SetIndexBuffer(indexBufferFloor);
		s_Data3D->floorVertexArray->AddVertexBuffer(vertexBufferFloor);
	}
	void Renderer3D::Shutdown() {
		HZ_PROFILE_FUNCTION();
		delete s_Data3D;
	}

	void Renderer3D::BeginScene(const PerspectiveCamera& camera) {
		HZ_PROFILE_FUNCTION();

		s_Data3D->shader->Bind();
		s_Data3D->shader->SetMat4("u_ViewProjection", camera.GetViewProjection());
	}
	void Renderer3D::EndScene() {}

	void Renderer3D::DrawCube(glm::vec3 position, glm::vec4 color) {
		{
			HZ_PROFILE_SCOPE("DrawCube3D - bind");
			s_Data3D->defaultTexture->Bind();
			s_Data3D->shader->Bind();
		}
		{
			HZ_PROFILE_SCOPE("DrawCube3D - uniforms");
			s_Data3D->shader->SetMat4("u_Transform", glm::translate(position));
			s_Data3D->shader->SetFloat4("u_Color", color);
		}
		{
			HZ_PROFILE_SCOPE("DrawCube3D - DrawIndexed");
			s_Data3D->vertexArray->Bind();
			RenderCommand::DrawIndexed(s_Data3D->vertexArray);
		}
	}
	void Renderer3D::DrawFloor() {
		HZ_PROFILE_FUNCTION();
		s_Data3D->checkeredTexture->Bind();
		s_Data3D->shader->Bind();

		s_Data3D->shader->SetMat4("u_Transform", glm::mat4(1.f));
		s_Data3D->shader->SetFloat4("u_Color", glm::vec4{1.f});

		s_Data3D->floorVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data3D->floorVertexArray);
	}

}