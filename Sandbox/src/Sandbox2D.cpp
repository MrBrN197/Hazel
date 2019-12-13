#include "Sandbox2D.h"

#include <imgui/imgui.h>

#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.f / 720.f) {
	
}


void Sandbox2D::OnAttach() {
	HZ_PROFILE_FUNCTION();
	m_CheckerboardTexture = Hazel::Texture2D::Create("assets/textures/Checkerboard.png");
};
void Sandbox2D::OnDetach() {};

void Sandbox2D::OnUpdate(Hazel::Timestep ts) {
	HZ_PROFILE_FUNCTION();
	// Update
	{
		HZ_PROFILE_SCOPE("Camera");
		m_CameraController.OnUpdate(ts);
	}

	// Render
	{
		HZ_PROFILE_SCOPE("Render Prep");
		Hazel::RenderCommand::ClearColor({ 0.25f, 0.65f, 0.35f, 1.f });
		Hazel::RenderCommand::Clear();

	}

	{
		Hazel::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Hazel::Renderer2D::DrawQuad({ 0.2f, 0.2f }, { 1.f, 1.f }, m_SquareColor);
		Hazel::Renderer2D::DrawQuad({ -0.5f, 1.f }, { 0.8f, 1.5f }, {0.8f, 0.2f, 0.3f, 1.f});
		Hazel::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1}, { 10.f, 10.f }, m_CheckerboardTexture);
		Hazel::Renderer2D::EndScene();
	}

	
};
void Sandbox2D::OnImGuiRender() {
	HZ_PROFILE_FUNCTION();
	ImGui::Begin("Sandbox2D");
	ImGui::SliderFloat4("Color", glm::value_ptr(m_SquareColor), 0.f, 1.f);
	ImGui::End();
};
void Sandbox2D::OnEvent(Hazel::Event& e) {
	m_CameraController.OnEvent(e);
};