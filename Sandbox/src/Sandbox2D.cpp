#include "Sandbox2D.h"

#include <imgui/imgui.h>

#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.f / 720.f) {
	
}


void Sandbox2D::OnAttach() {};
void Sandbox2D::OnDetach() {};

void Sandbox2D::OnUpdate(Hazel::Timestep ts) {
	m_CameraController.OnUpdate(ts);

	Hazel::Renderer2D::BeginScene(m_CameraController.GetCamera());

	Hazel::RenderCommand::ClearColor({ 0.25f, 0.65f, 0.35f, 1.f });
	Hazel::RenderCommand::Clear();
	Hazel::Renderer2D::DrawQuad({ 0.f, 0.f }, { 1.f, 1.f }, m_SquareColor);

	Hazel::Renderer2D::EndScene();

};
void Sandbox2D::OnImGuiRender() {
	ImGui::Begin("Sandbox2D");
	ImGui::SliderFloat4("Color", glm::value_ptr(m_SquareColor), 0.f, 1.f);
	ImGui::End();
};
void Sandbox2D::OnEvent(Hazel::Event& e) {
	m_CameraController.OnEvent(e);
};