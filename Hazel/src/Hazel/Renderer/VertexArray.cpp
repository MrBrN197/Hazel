#include "hzpch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Hazel/Renderer/RendererAPI.h"


namespace Hazel {
	Ref<VertexArray> VertexArray::Create() {
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API::None: HZ_CORE_ASSERT(false, " RendererAPI::None is currently not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateScope<OpenGLVertexArray>();
		}

		HZ_CORE_ASSERT(false, " RenderAPI not recognized");
		return nullptr;
	}


}