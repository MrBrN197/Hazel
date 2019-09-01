#include "hzpch.h"
#include "Renderer.h"
#include "Platform\OpenGL\OpenGLShader.h"

namespace Hazel {

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc) {

		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: HZ_CORE_ASSERT(false, " RendererAPI::None is currently not supported"); return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		HZ_CORE_ASSERT(false, " RenderAPI not recognized");
		return nullptr;
	}

	Shader* Shader::Create(const std::string& path) {

		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: HZ_CORE_ASSERT(false, " RendererAPI::None is currently not supported"); return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLShader(path);
		}

		HZ_CORE_ASSERT(false, " RenderAPI not recognized");
		return nullptr;
	}

}
