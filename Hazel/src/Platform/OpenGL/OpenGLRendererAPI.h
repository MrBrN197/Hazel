#pragma once
#include "Hazel/Renderer/RendererAPI.h"
#include "Hazel/Renderer/VertexArray.h"

namespace Hazel{

	class OpenGLRendererAPI : public RendererAPI {
	public:
		void Init() override;
		virtual void SetViewportSize(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
		void Clear() override;
		void ClearColor(const glm::vec4& color) override;
	};

}