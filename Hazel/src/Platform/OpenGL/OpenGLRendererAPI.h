#pragma once
#include "Hazel/Renderer/RendererAPI.h"
#include "Hazel/Renderer/VertexArray.h"

namespace Hazel{

	class OpenGLRendererAPI : public RendererAPI {
	public:
		void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
		void Clear() override;
		void ClearColor(const glm::vec4& color) override;
	};

}