#pragma once
#include <string>
#include "Hazel/Renderer/Shader.h"
#include <glm/glm.hpp>

typedef unsigned int GLenum;

namespace Hazel {

	class OpenGLShader : public Shader{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		OpenGLShader(const std::string& path);
		std::string ReadFile(const std::string& path);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& path);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		inline uint32_t GetRendererID() const { return  m_RendererID; }

		uint32_t GetUniformLocation(const char* name);
		void SetUniformInt(const char* name, int value);

		void SetUniformFloat(const char* name, float value);
		void SetUniformFloat2(const char* name, const glm::vec2& value);
		void SetUniformFloat3(const char* name, const glm::vec3& value);
		void SetUniformFloat4(const char* name, const glm::vec4& value);

		void SetUniformMat3(const char* name, const glm::mat3& values);
		void SetUniformMat4(const char* name, const glm::mat4& values);
	private:
		uint32_t m_RendererID;
	};

}