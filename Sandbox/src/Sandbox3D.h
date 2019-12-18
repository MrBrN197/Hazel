#pragma once
#include <Hazel.h>

class Sandbox3D : public Hazel::Layer {
public:
	Sandbox3D();
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Hazel::Timestep ts) override;
	virtual void OnEvent(Hazel::Event& e) override;
	virtual void OnImGuiRender() override;
private:
	bool OnMouseMoved(Hazel::MouseMovedEvent& e);
private:
	Hazel::PerspectiveCameraController m_CameraController;
	glm::vec4 m_Color = {0.85f, 0.2f, 0.3f, 1.f};
	glm::vec3 m_Position = { 0.f, 0.f, 0.f};
};