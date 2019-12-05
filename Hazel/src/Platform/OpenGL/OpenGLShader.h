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
		uint32_t GetUniformLocation(const std::string& name);
	public:
		virtual void Bind() const override;
		virtual void Unbind() const override;
		inline uint32_t GetRendererID() const { return  m_RendererID; }

		virtual const std::string& GetName() const { return m_Name; }

		virtual void SetFloat3(const std::string& name, const glm::vec3& value) override;
		virtual void SetFloat4(const std::string name, const glm::vec4& value) override;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) override;
		virtual void SetInt(const std::string& name, int value) override;

	private:
		void UploadUniformInt(const std::string& name, int value);

		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

		void UploadUniformMat3(const std::string& name, const glm::mat3& values);
		void UploadUniformMat4(const std::string& name, const glm::mat4& values);
	private:
		uint32_t m_RendererID;
		std::string m_Name;
	};

}