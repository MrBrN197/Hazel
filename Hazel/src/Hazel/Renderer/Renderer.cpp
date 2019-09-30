#include "hzpch.h"
#include "Renderer.h"
#include "Hazel/Renderer/RenderCommand.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Hazel {

	Renderer::SceneData Renderer::s_SceneData;

	void Renderer::Init() {
		RenderCommand::Init();
	}
	void Renderer::BeginScene(PerspectiveCamera camera) {
		s_SceneData	= { camera.GetViewProjection() };
	}
	void Renderer::EndScene() {}
	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform) {
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(shader)->Bind();
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(shader)->SetUniformMat4("u_ViewProjection", s_SceneData.viewProjection);
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(shader)->SetUniformMat4("u_Transform", transform);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}