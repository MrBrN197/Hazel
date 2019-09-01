#pragma once
#include "Hazel/Renderer/VertexArray.h"
#include <glm/glm.hpp>
#include "Hazel/Renderer/RendererAPI.h"

namespace Hazel {

	class RenderCommand{
	public:
		static void RenderCommand::Init() {
			s_RendererAPI->Init();
		}
		static void RenderCommand::DrawIndexed(const Ref<VertexArray>& vertexArray) {
			s_RendererAPI->DrawIndexed(vertexArray);
		}
		static void RenderCommand::ClearColor(const glm::vec4& color) {
			s_RendererAPI->ClearColor(color);
		}
		static void RenderCommand::Clear() {
			s_RendererAPI->Clear();
		}

		static RendererAPI* s_RendererAPI;
	};

}