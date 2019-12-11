#include "hzpch.h"
#include "Texture.h"

#include "Platform/OpenGL/OpenGLTexture2D.h"

#include "Renderer.h"

namespace Hazel {

	Ref<Texture2D> Texture2D::Create(const std::string& path) {

		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: HZ_CORE_ASSERT(false, " RendererAPI::None is currently not supported"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(path);
		}

		HZ_CORE_ASSERT(false, " RenderAPI not recognized");
		return nullptr;
	}


}