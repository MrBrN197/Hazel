#pragma once
#include <string>
#include "Hazel/Renderer/Shader.h"
#include <glm/glm.hpp>

typedef unsigned int GLenum;

namespace Hazel {

	class OpenGLShader : public Shader{
	public:
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		OpenGLShader(const std::string& path);
		virtual ~OpenGLShader();
	private:
		std::string ReadFile(const std::string& path);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& path);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
		uint32_t GetUniformLocation(const char* name);
	public:
		virtual void Bind() const override;
		virtual void Unbind() const override;
		inline uint32_t GetRendererID() const { return  m_RendererID; }

		virtual const std::string& GetName() const { return m_Name; }
	public:
		void SetUniformInt(const char* name, int value);

		void SetUniformFloat(const char* name, float value);
		void SetUniformFloat2(const char* name, const glm::vec2& value);
		void SetUniformFloat3(const char* name, const glm::vec3& value);
		void SetUniformFloat4(const char* name, const glm::vec4& value);

		void SetUniformMat3(const char* name, const glm::mat3& values);
		void SetUniformMat4(const char* name, const glm::mat4& values);
	private:
		uint32_t m_RendererID;
		std::string m_Name;
	};

}