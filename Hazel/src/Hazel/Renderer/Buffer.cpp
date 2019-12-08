#include "hzpch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform\OpenGL\OpenGLBuffer.h"

namespace Hazel {

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size) {

		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API::None: HZ_CORE_ASSERT(false, " RendererAPI::None is currently not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_unique<OpenGLVertexBuffer>(vertices, size);
		}

		HZ_CORE_ASSERT(false, " RenderAPI not recognized");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count) {
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API::None: HZ_CORE_ASSERT(false, " No implementation for None API"); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_unique<OpenGLIndexBuffer>(indices, count);
		}

		HZ_CORE_ASSERT(false, " RenderAPI not recognized");
		return nullptr;
	}

}
