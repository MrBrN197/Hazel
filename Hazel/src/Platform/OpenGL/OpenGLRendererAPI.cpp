#include "hzpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Hazel {

	void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) {
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
	void OpenGLRendererAPI::Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void OpenGLRendererAPI::ClearColor(const glm::vec4& color) {
		glClearColor(color.r, color.g, color.b, color.a);
	}
	void OpenGLRendererAPI::EnableDepthTesting() {
		glEnable(GL_DEPTH_TEST);
	}
	void OpenGLRendererAPI::DisableDepthTesting() {
		glDisable(GL_DEPTH_TEST);
	}

}