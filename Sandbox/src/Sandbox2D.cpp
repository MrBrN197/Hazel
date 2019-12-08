#include "Sandbox2D.h"

#include <imgui/imgui.h>

#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.f / 720.f) {

	float vertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
	};

	m_SquareVA = Hazel::VertexArray::Create();
	Hazel::Ref<Hazel::VertexBuffer> vertexBuffer(Hazel::VertexBuffer::Create(vertices, sizeof(vertices)));

	uint32_t indices[3 * 2] = {
		0, 1, 2,
		0, 2, 3
	};
	Hazel::Ref<Hazel::IndexBuffer> indexBuffer(Hazel::IndexBuffer::Create(indices, 3 * 4));
	m_SquareVA->SetIndexBuffer(indexBuffer);

	Hazel::BufferLayout layout({
		{Hazel::ShaderDataType::Float3, "a_Position"}
	});
	vertexBuffer->SetLayout(layout);
	m_SquareVA->AddVertexBuffer(vertexBuffer);


	m_FlatColorShader = Hazel::Shader::Create("assets/shaders/FlatColor.glsl");
}


void Sandbox2D::OnAttach() {};
void Sandbox2D::OnDetach() {};

void Sandbox2D::OnUpdate(Hazel::Timestep ts) {
	m_CameraController.OnUpdate(ts);

	Hazel::Renderer::BeginScene(m_CameraController.GetCamera());

	Hazel::RenderCommand::ClearColor({ 0.25f, 0.65f, 0.35f, 1.f });
	Hazel::RenderCommand::Clear();

	m_FlatColorShader->Bind();
	m_FlatColorShader->SetFloat4("u_Color", m_SquareColor);

	//glm::mat4 transform = glm::translate(m_PrismPosition) * glm::rotate(glm::radians(m_PrismRotation), glm::vec3(0.0f, 1.f, 0.f));
	glm::mat4 transform = glm::mat4(1.f);
	Hazel::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);

	Hazel::Renderer::EndScene();

};
void Sandbox2D::OnImGuiRender() {
	ImGui::Begin("Sandbox2D");
	ImGui::SliderFloat4("Color", glm::value_ptr(m_SquareColor), 0.f, 1.f);
	ImGui::End();
};
void Sandbox2D::OnEvent(Hazel::Event& e) {
	m_CameraController.OnEvent(e);
};