#pragma once

#include "PerspectiveCamera.h"

#include "Hazel/Core/Timestep.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/KeyEvent.h"


namespace Hazel {

	class PerspectiveCameraController {
	public:
		PerspectiveCameraController(float fov, float aspectRatio, float nearClip = 1.f, float farClip = 100.f);
		~PerspectiveCameraController() = default;

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		PerspectiveCamera& GetCamera() { return m_Camera; }
	private:
		bool OnMouseScroll(MouseScrollEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		bool OnKeyPressed(KeyPressedEvent& e);
	private:
		PerspectiveCamera m_Camera;
		glm::vec3 m_CameraPosition = { 0.f, 0.f, 10.f };
		float m_CameraRotation = 0.f;

		float m_CameraMoveSpeed = 5.f;
		float m_CameraRotationSpeed = 4.f;

		glm::vec2 m_LastMousePosition;
	};

}