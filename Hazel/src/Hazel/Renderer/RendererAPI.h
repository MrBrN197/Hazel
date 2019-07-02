#pragma once
#include <glm/glm.hpp>
#include "Hazel/Renderer/VertexArray.h"

namespace Hazel {

	class RendererAPI {
	public:
		enum class API {
			None = 0, OpenGL
		};
	public:
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;
		virtual void Clear() = 0;
		virtual void ClearColor(const glm::vec4& color) = 0;

		static inline API GetAPI() { return s_API; }
	private:
		static API s_API;
	};
}