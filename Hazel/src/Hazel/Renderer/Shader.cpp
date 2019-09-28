#include "hzpch.h"
#include "Renderer.h"
#include "Platform\OpenGL\OpenGLShader.h"

namespace Hazel {

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) {

		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: HZ_CORE_ASSERT(false, " RendererAPI::None is currently not supported"); return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}

		HZ_CORE_ASSERT(false, " RenderAPI not recognized");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& path) {

		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: HZ_CORE_ASSERT(false, " RendererAPI::None is currently not supported"); return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(path);
		}

		HZ_CORE_ASSERT(false, " RenderAPI not recognized");
		return nullptr;
	}

	
	Ref<Shader> ShaderLibrary::Load(const std::string& filepath) {
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}
	Ref<Shader> ShaderLibrary::ShaderLibrary::Load(const std::string& name, const std::string& filepath) {
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}
	void ShaderLibrary::Add(const std::string& name, Ref<Shader>& shader) {
		HZ_ASSERT(!Exists(name), "Shader already exists");
		m_Shaders[name] = shader;
	}
	void ShaderLibrary::Add(Ref<Shader>& shader) {
		const std::string& name = shader->GetName();
		HZ_ASSERT(!Exists(name), "Shader already exists");
		m_Shaders[name] = shader;
	}
	
	Ref<Shader> ShaderLibrary::Get(const std::string& name) {
		HZ_ASSERT(m_Shaders.find(name) != m_Shaders.end(), "Shader doesn't exist");
		return m_Shaders[name];
	}

}
