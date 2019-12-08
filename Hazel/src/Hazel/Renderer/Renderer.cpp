#include "hzpch.h"
#include "Renderer.h"
#include "Hazel/Renderer/RenderCommand.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include "Renderer2D.h"

namespace Hazel {

	Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData>();

	void Renderer::Init() {
		RenderCommand::Init();
		Renderer2D::Init();
	}
	void Renderer::OnWindowResize(uint32_t width, uint32_t height){
		RenderCommand::SetViewportSize(0, 0, width, height);
	}
	void Renderer::BeginScene(PerspectiveCamera camera) {
		*s_SceneData = { camera.GetViewProjection() };
	}
	void Renderer::BeginScene(OrthographicCamera camera) {
		*s_SceneData = { camera.GetViewProjection() };
	}
	void Renderer::EndScene() {}
	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform) {
		shader->Bind();
		shader->SetMat4("u_ViewProjection", s_SceneData->viewProjection);
		shader->SetMat4("u_Transform", transform);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}