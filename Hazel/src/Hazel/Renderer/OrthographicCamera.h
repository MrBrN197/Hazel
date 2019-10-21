#pragma once
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtx/transform2.hpp>
//#include <glm/gtx/euler_angles.hpp>


namespace Hazel {
	class OrthographicCamera {
	public:
		OrthographicCamera(float left, float right, float bottom, float top)
			: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.f, 1.f)), m_ViewMatrix(1.f)
		{
		}
		void SetProjection(float left, float right, float bottom, float top) {
			m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.f, 1.f);
		}

		void SetPosition(const glm::vec3& translate) {
			m_Position = translate;
			RecalculateViewMatrix();
		}
		void SetRotation(float rotate) {
			m_Rotation = rotate;
			RecalculateViewMatrix();
		}

		const glm::mat4 GetViewProjection() const {
			return m_ProjectionMatrix * m_ViewMatrix;
		}
		void RecalculateViewMatrix() {
			glm::mat4 transform = glm::translate(m_Position) * glm::rotate(glm::radians(m_Rotation), glm::vec3(0.f, 0.f, 1.f));
			//glm::mat4 rotate = glm::rotate(glm::radians(-m_Rotation), glm::vec3(0.f, 1.f, 0.f));
			m_ViewMatrix = glm::inverse(transform);
		}
	private:
		glm::mat4 m_ViewMatrix = glm::mat4(1.f);
		glm::mat4 m_ProjectionMatrix;

		glm::vec3 m_Position = { 0.f, 0.f, 0.f };
		float m_Rotation = 0.f;
	};
}