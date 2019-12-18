#include "hzpch.h"
#include "PerspectiveCameraController.h"

#include "Hazel/Core/Input.h"
#include "Hazel/Core/KeyCodes.h"
#include "Hazel/Core/MouseButtonCodes.h"
#include "Hazel/Core/Application.h"


constexpr float PI = 3.14159265358979323f;
namespace Hazel{

	PerspectiveCameraController::PerspectiveCameraController(float fov, float aspectRatio, float nearClip, float farClip)
	: m_Camera(fov, aspectRatio, 1.f, nearClip, farClip) {
		auto mousePosition = Input::GetMousePosition();
		m_LastMousePosition = { mousePosition.first, mousePosition.second };
	}
	void PerspectiveCameraController::OnUpdate(Timestep ts) {
		HZ_PROFILE_FUNCTION();

		float angle = glm::radians(m_CameraRotation);

		glm::vec3 movement = { 0.f, 0.f, 0.f };
		if (Input::IsKeyPressed(HZ_KEY_A)) {
			movement.z -= cos(angle + PI/2) * m_CameraMoveSpeed * ts;
			movement.x -= sin(angle + PI/2) * m_CameraMoveSpeed * ts;
		}
		else if (Input::IsKeyPressed(HZ_KEY_D)) {
			movement.z -= cos(angle - PI/2) * m_CameraMoveSpeed * ts;
			movement.x -= sin(angle - PI/2) * m_CameraMoveSpeed * ts;
		}
		if (Input::IsKeyPressed(HZ_KEY_W)) {
			movement.z -= cos(angle) * m_CameraMoveSpeed * ts;
			movement.x -= sin(angle) * m_CameraMoveSpeed * ts;
		}
		else if (Input::IsKeyPressed(HZ_KEY_S)) {
			movement.z -= cos(angle - PI) * m_CameraMoveSpeed * ts;
			movement.x -= sin(angle - PI) * m_CameraMoveSpeed * ts;
		}
		if (glm::length(movement)) {
			movement = glm::normalize(movement) * (m_CameraMoveSpeed * ts);
		}
		m_CameraPosition += movement;

		static float t = 0.0f;
		if (Input::IsMouseButtonPressed(HZ_MOUSE_BUTTON_RIGHT)) {
			float duration = 0.1f;
			if(t < 1.f)
				t = std::min(t + (ts/duration), 1.f);
			float s = 45.f;
			float e = 20.f;
			float fov = s * pow(1-t, 3)
				+ (s - 20.f) * pow(1-t, 2) * pow(t, 1) * 3 
				+ (e + 20.f) * pow(1-t, 1) * pow(t, 2) * 3
				+ e * pow(t, 3);
			m_Camera.SetFov(fov);
		}
		else {
			t = 0.f;
			m_Camera.SetFov(45.f);
		}

		auto mousePos = Input::GetMousePosition();
		glm::vec2 currentMousePos = {mousePos.first, mousePos.second};

		uint32_t width = 1280;
		if (currentMousePos.x >= width) {
			currentMousePos.x = currentMousePos.x - (width-1);
			m_LastMousePosition.x = 0.0f;
			Input::SetMouseX(currentMousePos.x);
		}
		else if (currentMousePos.x < 0) {
			currentMousePos.x = (width - 1) + currentMousePos.x;
			m_LastMousePosition.x = (float)(width - 1);
			Input::SetMouseX(currentMousePos.x);
		}

		glm::vec2 mouseDelta = currentMousePos - m_LastMousePosition;
		m_CameraRotation -= mouseDelta.x * m_CameraRotationSpeed * ts;
		m_LastMousePosition = currentMousePos;

		if (m_CameraRotation > 180.0f)
			m_CameraRotation -= 360.0f;
		else if (m_CameraRotation <= -180.0f)
			m_CameraRotation += 360.0f;

		m_Camera.SetRotation(m_CameraRotation);
		m_Camera.SetPosition(m_CameraPosition);

	}

	void PerspectiveCameraController::OnEvent(Event& e) {
		HZ_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrollEvent>(HZ_BIND_EVENT_FN(PerspectiveCameraController::OnMouseScroll));
		dispatcher.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(PerspectiveCameraController::OnWindowResize));
		dispatcher.Dispatch<KeyPressedEvent>(HZ_BIND_EVENT_FN(PerspectiveCameraController::OnKeyPressed));
	}

	bool PerspectiveCameraController::OnMouseScroll(MouseScrollEvent& e)
	{
		HZ_PROFILE_FUNCTION();

		//m_ZoomLevel -= e.GetYOffset() * 0.25f;
		//m_ZoomLevel = std::max(0.25f, m_ZoomLevel);
		//m_Camera.SetProjection(-m_ZoomLevel * m_AspectRatio, m_ZoomLevel * m_AspectRatio, -m_ZoomLevel, m_ZoomLevel);
		//m_CameraMoveSpeed = m_ZoomLevel;
		return false;
	}

	bool PerspectiveCameraController::OnWindowResize(WindowResizeEvent& e)
	{
		HZ_PROFILE_FUNCTION();

		//float aspectRatio = e.GetWidth() / e.GetHeight();
		//m_Camera.SetProjection(m_Fov, m_Width*aspectRatio, m_Height, 1.f, 100.f);
		return false;
	}

	bool PerspectiveCameraController::OnKeyPressed(KeyPressedEvent& e) {
		if (e.GetKeyCode() == HZ_KEY_ESCAPE) {
			Application::Get().GetWindow().ToggleCursorVisibility();
		}
		return false;
	}


}