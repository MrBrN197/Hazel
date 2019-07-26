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
			glm::mat4 temporaryMatrix = glm::translate(glm::vec3(0.f, 0.f, -5.f));
			return m_ProjectionMatrix * temporaryMatrix;
		}
		void RecalculateViewMatrix() {
			glm::mat4 translate = glm::translate(m_Translation);
			glm::mat4 rotate = glm::rotate(m_Rotation, glm::vec3(0.f, 1.f, 0.f));
			m_ViewMatrix = glm::inverse(translate * rotate);
		}
	private:
		glm::vec3 m_Translation = { 0.f, 0.f, 0.f };
		float m_Rotation = 0.f;
		glm::mat4 m_ViewMatrix = glm::mat4(1.f);
		glm::mat4 m_ProjectionMatrix;
	};
}