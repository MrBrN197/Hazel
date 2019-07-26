#include "hzpch.h"
#include "Renderer.h"
#include "Hazel/Renderer/RenderCommand.h"

namespace Hazel {

	Renderer::SceneData Renderer::s_SceneData;

	void Renderer::BeginScene(PerspectiveCamera camera) {
		s_SceneData	= { camera.GetViewProjection() };
	}
	void Renderer::EndScene() {}
	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform) {
		shader->Bind();
		shader->SetUniformMat4("u_ViewProjeciton", s_SceneData.viewProjection);
		shader->SetUniformMat4("u_Transform", transform);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}