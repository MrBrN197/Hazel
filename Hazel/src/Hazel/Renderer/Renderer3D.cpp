#include "hzpch.h"
#include "Renderer3D.h"
#include "RenderCommand.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"

#include <glad/glad.h>

#define VERTEX_SIZE sizeof(float) * 3
#define MAX_VERTICES 1000000
#define MAX_INDICES_SIZE MAX_VERTICES * VERTEX_SIZE
#define MAX_VERTEX_SIZE (1ULL << 32) - 1

namespace Hazel {
	
	struct Renderer3DStorage {
		Ref<Shader> shader;
		Ref<Texture2D> defaultTexture;
		Ref<VertexArray> defaultVertexArray;
		Ref<VertexArray> floorVertexArray;
		Ref<Texture2D> checkeredTexture;
		Ref<VertexArray> meshVertexArray;
		uint32_t indexBufferOffset = 0;
		uint32_t vertexBufferOffset = 0;
		uint32_t maxIndex = 0;
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

		s_Data3D->defaultVertexArray = VertexArray::Create();
		s_Data3D->defaultVertexArray->Bind();
		uint32_t indices[36] = {
			0, 1, 2, 0, 2, 3, // Front
			4, 5, 6, 4, 6, 7, // Back
			4, 0, 3, 4, 3, 7, // Left
			1, 5, 6, 1, 6, 2, // Right
			3, 2, 6, 3, 6, 7, // Top
			1, 0, 4, 1, 4, 5  // Bottom
		};
		float vertices[8 * 8] = {
			-0.5f, -0.5f, 0.5f, 0.f, 1.f, 0.f, 0.f, 0.f,
			 0.5f, -0.5f, 0.5f, 0.f, 1.f, 0.f, 1.f, 0.f,
			 0.5f,  0.5f, 0.5f, 0.f, 1.f, 0.f, 1.f, 1.f,
			-0.5f,  0.5f, 0.5f, 0.f, 1.f, 0.f, 0.f, 1.f,
			-0.5f, -0.5f,-0.5f, 0.f, 1.f, 0.f, 0.f, 0.f,
			 0.5f, -0.5f,-0.5f, 0.f, 1.f, 0.f, 1.f, 0.f,
			 0.5f,  0.5f,-0.5f, 0.f, 1.f, 0.f, 1.f, 1.f,
			-0.5f,  0.5f,-0.5f, 0.f, 1.f, 0.f, 0.f, 1.f
		};
		auto indexBuffer = IndexBuffer::Create(indices, 36);
		auto vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
		vertexBuffer->SetLayout({
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float3, "a_Normal"},
			{ShaderDataType::Float2, "a_TexCoord"}
		});

		s_Data3D->defaultVertexArray->SetIndexBuffer(indexBuffer);
		s_Data3D->defaultVertexArray->AddVertexBuffer(vertexBuffer);


		// FLOOR

		s_Data3D->floorVertexArray = VertexArray::Create();
		s_Data3D->floorVertexArray->Bind();
		uint32_t floorIndices[6] = { 0, 1, 2, 0, 2, 3};
		float floorVertices[4 * 8] = {
			-20.5f, -0.5f,  20.5f, 0.f, 1.f, 0.f, 0.f, 0.f,
			 20.5f, -0.5f,  20.5f, 0.f, 1.f, 0.f, 1.f, 0.f,
			 20.5f, -0.5f, -20.5f, 0.f, 1.f, 0.f, 1.f, 1.f,
			-20.5f, -0.5f, -20.5f, 0.f, 1.f, 0.f, 0.f, 1.f
		};
		auto indexBufferFloor = IndexBuffer::Create(floorIndices, 6);
		auto vertexBufferFloor = VertexBuffer::Create(floorVertices, sizeof(floorVertices));
		vertexBufferFloor->SetLayout({
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float3, "a_Normal"},
			{ShaderDataType::Float2, "a_TexCoord"}
		});

		s_Data3D->floorVertexArray->SetIndexBuffer(indexBufferFloor);
		s_Data3D->floorVertexArray->AddVertexBuffer(vertexBufferFloor);



		// BATCH BUFFER
		s_Data3D->meshVertexArray = VertexArray::Create();
		s_Data3D->meshVertexArray->Bind();

		Ref<VertexBuffer> mesh_vertexBuffer = VertexBuffer::Create(NULL, (uint32_t)MAX_VERTEX_SIZE);
		Ref<IndexBuffer> mesh_indexBuffer = IndexBuffer::Create(NULL, MAX_INDICES_SIZE);
		mesh_indexBuffer->SetCount(0);

		mesh_vertexBuffer->SetLayout({
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float3, "a_Normal"},
			{ShaderDataType::Float2, "a_TexCoord"}
		});

		s_Data3D->meshVertexArray->AddVertexBuffer(mesh_vertexBuffer);
		s_Data3D->meshVertexArray->SetIndexBuffer(mesh_indexBuffer);

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

	void Renderer3D::DrawCube(const glm::vec3& position, const glm::vec4& color) {
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
			s_Data3D->defaultVertexArray->Bind();
			RenderCommand::DrawIndexed(s_Data3D->defaultVertexArray);
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

	void Renderer3D::Submit(const Mesh& mesh) {
		HZ_PROFILE_FUNCTION();
		//HZ_CORE_ASSERT(mesh.m_Indices.size() <= MAX_INDICES_SIZE, "");
		//HZ_CORE_ASSERT(mesh.m_Vertices.size() <= MAX_VERTEX_SIZE, "");

		//s_Data3D->meshVertexArray->Bind();

		//float temp[8];
		//int vertexSize = sizeof(float) * 8;
		//for (size_t i = 0; i < mesh.m_Vertices.size(); i++) {
		//	float* ptr = temp;
		//	*(glm::vec3*)ptr = mesh.m_Vertices[i];
		//	ptr += 3;
		//	*(glm::vec3*)ptr = mesh.m_Normals[i];
		//	ptr += 3;
		//	*(glm::vec2*)ptr = mesh.m_TexCoords[i];

		//	glBufferSubData(GL_ARRAY_BUFFER, s_Data3D->vertexBufferOffset + i * vertexSize, vertexSize, temp);
		//}

		//glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, s_Data3D->indexBufferOffset, sizeof(uint32_t)*mesh.m_Indices.size(), mesh.m_Indices.data());


		//s_Data3D->indexBufferOffset += (uint32_t) mesh.m_Indices.size();
		//s_Data3D->vertexBufferOffset += (uint32_t)mesh.m_Vertices.size() * vertexSize;
		//s_Data3D->meshVertexArray->GetIndexBuffer()->SetCount(s_Data3D->indexBufferOffset);

		//return;

		auto indexBuffer = s_Data3D->meshVertexArray->GetIndexBuffer();
		HZ_CORE_ASSERT(s_Data3D->meshVertexArray->GetVertexBuffers().size() == 1, "VertexArray Vertex Buffers Not Equal To 1");
		auto vertexBuffer = s_Data3D->meshVertexArray->GetVertexBuffers()[0];

		uint32_t numVertices = (uint32_t)mesh.m_Vertices.size();
		float* data = (float*)vertexBuffer->MapBuffer() + s_Data3D->vertexBufferOffset;


		HZ_CORE_ASSERT(sizeof(glm::vec3) == (sizeof(float) * 3), "sizeof(glm::vec3) != 12");
		HZ_CORE_ASSERT(sizeof(glm::vec2) == (sizeof(float) * 2), "sizeof(glm::vec2) != 8");

		for (uint32_t i = 0; i < numVertices; i++) {
			glm::vec3 v = mesh.m_Vertices[i];
			glm::vec3 n = mesh.m_Normals[i];
			glm::vec2 t = mesh.m_TexCoords[i];

			*(glm::vec3*)data = v;
			data += 3;
			*(glm::vec3*)data = n;
			data += 3;
			*(glm::vec2*)data = t;
			data += 2;
		}
		vertexBuffer->UnmapBuffer();


		uint32_t* indices = (uint32_t*)indexBuffer->MapBuffer() + s_Data3D->indexBufferOffset;
		uint32_t size = (uint32_t)mesh.m_Indices.size();
		for (uint32_t i = 0; i < size; i++) {
			*indices++ = (s_Data3D->vertexBufferOffset)/8 + mesh.m_Indices[i];
		}
		indexBuffer->UnmapBuffer();


		s_Data3D->vertexBufferOffset += numVertices * 8;
		s_Data3D->indexBufferOffset += size;
		indexBuffer->SetCount(s_Data3D->indexBufferOffset);

	}

	void Renderer3D::Flush() {

		HZ_PROFILE_FUNCTION();
		s_Data3D->defaultTexture->Bind();
		s_Data3D->shader->Bind();

		static float angle = 0.f;
		angle += 0.01f;
		glm::mat4 transform = glm::rotate(angle, glm::vec3{ 0.f, 1.f, 0.f });
		//glm::mat4 transform(1.f);
		s_Data3D->shader->SetMat4("u_Transform", transform);
		s_Data3D->shader->SetFloat4("u_Color", glm::vec4{ 1.f });

		s_Data3D->meshVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data3D->meshVertexArray);
	}

}