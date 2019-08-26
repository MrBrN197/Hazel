#pragma once
#include "Hazel/Renderer/VertexArray.h"
#include <glm/glm.hpp>
#include "Hazel/Renderer/RendererAPI.h"

namespace Hazel {

	class RenderCommand{
	public:
		static void RenderCommand::DrawIndexed(const Ref<VertexArray>& vertexArray) {
			s_RendererAPI->DrawIndexed(vertexArray);
		}
		static void RenderCommand::ClearColor(const glm::vec4& color) {
			s_RendererAPI->ClearColor(color);
		}
		static void RenderCommand::Clear() {
			s_RendererAPI->Clear();
		}
		static void RenderCommand::EnableDepthTesting() {
			s_RendererAPI->EnableDepthTesting();
		}
		static void RenderCommand::DisableDepthTesting() {
			s_RendererAPI->DisableDepthTesting();
		}

		static RendererAPI* s_RendererAPI;
	};

}