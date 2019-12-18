#include "Sandbox3D.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

Sandbox3D::Sandbox3D() : m_CameraController(45.f, 1.778f) {}

void Sandbox3D::OnAttach() {
	HZ_INFO("Sandbox3D Attached");
}
void Sandbox3D::OnDetach() {
	HZ_INFO("Sandbox3D Detached");
}
void Sandbox3D::OnUpdate(Hazel::Timestep ts) {

	m_CameraController.OnUpdate(ts);

	Hazel::RenderCommand::ClearColor({ 0.2f, 0.2f, 0.2f, 1.f });
	Hazel::RenderCommand::Clear();

	Hazel::Renderer3D::BeginScene(m_CameraController.GetCamera());
	Hazel::Renderer3D::DrawFloor();
	//Hazel::Renderer3D::DrawCube(m_Position, m_Color);
	//Hazel::Renderer3D::DrawCube({ 1.f, 0.f, 0.f }, { 0.2f, 0.3f, 0.8f, 1.f });
	Hazel::Renderer3D::DrawCubeMesh({1.f, 0.f, 0.f}, {0.2f, 0.3f, 0.8f, 1.f});
	Hazel::Renderer3D::EndScene();

}
void Sandbox3D::OnEvent(Hazel::Event& e) {
	Hazel::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Hazel::MouseMovedEvent>(HZ_BIND_EVENT_FN(Sandbox3D::OnMouseMoved));
	
	m_CameraController.OnEvent(e);
}

bool Sandbox3D::OnMouseMoved(Hazel::MouseMovedEvent& e) {
	uint32_t width = Hazel::Application::Get().GetWindow().GetWidth();
	if (e.GetX() > width) {
	}
	return false;
}

void Sandbox3D::OnImGuiRender() {
	ImGui::Begin("Sandbox3D");
	ImGui::SliderFloat3("Position", glm::value_ptr(m_Position), -10.f, 10.f);
	ImGui::SliderFloat4("Color", glm::value_ptr(m_Color),  0.f, 1.f);
	ImGui::End();
}


