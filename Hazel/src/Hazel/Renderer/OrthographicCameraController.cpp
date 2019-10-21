#include "hzpch.h"
#include "OrthographicCamera.h"
#include "OrthographicCameraController.h"
#include "Hazel/Input.h"
#include "Hazel/KeyCodes.h"

Hazel::OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
	: m_AspectRatio(aspectRatio), m_Camera(-m_ZoomLevel * m_AspectRatio, m_ZoomLevel * m_AspectRatio, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation) {
}

void Hazel::OrthographicCameraController::OnUpdate(Timestep ts)
{
	if (Input::IsKeyPressed(HZ_KEY_A)) {
		m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraMoveSpeed * ts;
		m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraMoveSpeed * ts;
	}
	else if (Input::IsKeyPressed(HZ_KEY_D)) {
		m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraMoveSpeed * ts;
		m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraMoveSpeed * ts;
	}
	if (Input::IsKeyPressed(HZ_KEY_W)) {
		m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraMoveSpeed * ts;
		m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraMoveSpeed * ts;
	}
	else if (Input::IsKeyPressed(HZ_KEY_S)) {
		m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraMoveSpeed * ts;
		m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraMoveSpeed * ts;
	}

	if (m_Rotation) {
		if (Input::IsKeyPressed(HZ_KEY_Q)) {
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		}
		else if (Input::IsKeyPressed(HZ_KEY_E)) {
			m_CameraRotation += m_CameraRotationSpeed * ts;
		}

		if (m_CameraRotation > 180.0f)
			m_CameraRotation -= 360.0f;
		else if (m_CameraRotation <= -180.0f)
			m_CameraRotation += 360.0f;

		m_Camera.SetRotation(m_CameraRotation);

	}


	m_Camera.SetPosition(m_CameraPosition);

}

void Hazel::OrthographicCameraController::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<MouseScrollEvent>(HZ_BIND_EVENT_FN(OrthographicCameraController::OnMouseScroll));
	dispatcher.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(OrthographicCameraController::OnWindowResize));
}

bool Hazel::OrthographicCameraController::OnMouseScroll(MouseScrollEvent& e)
{	
	m_ZoomLevel -= e.GetYOffset() * 0.25f;
	m_ZoomLevel = std::max(0.25f, m_ZoomLevel);
	m_Camera.SetProjection(-m_ZoomLevel * m_AspectRatio, m_ZoomLevel * m_AspectRatio, -m_ZoomLevel, m_ZoomLevel);
	m_CameraMoveSpeed = m_ZoomLevel;
	return false;
}

bool Hazel::OrthographicCameraController::OnWindowResize(WindowResizeEvent& e)
{
	m_AspectRatio = e.GetWidth() / e.GetHeight();
	m_Camera.SetProjection(-m_ZoomLevel * m_AspectRatio, m_ZoomLevel * m_AspectRatio, -m_ZoomLevel, m_ZoomLevel);
	return false;
}
