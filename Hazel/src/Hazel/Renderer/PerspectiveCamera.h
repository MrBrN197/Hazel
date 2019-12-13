#pragma once
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtx/transform2.hpp>
//#include <glm/gtx/euler_angles.hpp>


namespace Hazel {
	class PerspectiveCamera {
	public:
		PerspectiveCamera(float fov, float width, float height, float nearClip, float farClip) {
			HZ_PROFILE_FUNCTION();

			m_ProjectionMatrix = glm::perspectiveFov(glm::radians(fov), width, height, nearClip, farClip);
		}

		void SetPosition(const glm::vec3& translate) {
			m_Translation = translate;
			RecalculateViewMatrix();
		}
		void SetRotation(float rotate) {
			m_Rotation = rotate;
			RecalculateViewMatrix();
		}

		const glm::mat4 GetViewProjection() const {
			HZ_PROFILE_FUNCTION();

			return m_ProjectionMatrix * m_ViewMatrix;
		}
		void RecalculateViewMatrix() {
			HZ_PROFILE_FUNCTION();

			glm::mat4 transform = glm::translate(m_Translation) * glm::rotate(glm::radians(m_Rotation), glm::vec3(0.f, 1.f, 0.f));
			//glm::mat4 rotate = glm::rotate(glm::radians(-m_Rotation), glm::vec3(0.f, 1.f, 0.f));
			m_ViewMatrix = glm::inverse(transform);
		}
	private:
		glm::vec3 m_Translation = { 0.f, 0.f, 0.f };
		float m_Rotation = 0.f;
		glm::mat4 m_ViewMatrix = glm::mat4(1.f);
		glm::mat4 m_ProjectionMatrix;
	};
}