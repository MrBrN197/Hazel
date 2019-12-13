#include "hzpch.h"
#include "OpenGLShader.h"

#include <fstream>

#include <glad\glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Hazel {

	static GLenum ShaderTypeFromString(const std::string& type) {
		HZ_PROFILE_FUNCTION();

		if (type == "vertex")
			return GL_VERTEX_SHADER;
		else if (type == "fragment")
			return GL_FRAGMENT_SHADER;

		HZ_ASSERT(false, "Invalid Shader Type");
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& path) {
		HZ_PROFILE_FUNCTION();

		std::string& source = ReadFile(path);
		std::unordered_map<GLenum, std::string> shaderSources = PreProcess(source);
		Compile(shaderSources);

		// Get shader name from filename
		size_t lastSlash = path.find_last_of("\\/");
		size_t period = path.rfind('.');
		size_t begin = (lastSlash == std::string::npos) ? 0 : lastSlash + 1;
		size_t span = (period == std::string::npos) ? path.size() - begin : period - begin;
		m_Name = path.substr(begin, span);
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) : m_Name(name) {
		HZ_PROFILE_FUNCTION();
		std::unordered_map<GLenum, std::string> shaderSources;
		shaderSources[GL_VERTEX_SHADER] = vertexSrc;
		shaderSources[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile(shaderSources);
	}

	std::string OpenGLShader::ReadFile(const std::string& path) {
		HZ_PROFILE_FUNCTION();

		std::string result;
		std::ifstream in(path, std::ios::in | std::ios::binary);
		if (in) {
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(std::ios::beg);
			in.read(&result[0], result.size());
		}
		else {
			HZ_CORE_ERROR("Failed To Open File {0}", path);
		}
		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source) {
		HZ_PROFILE_FUNCTION();
		std::unordered_map<GLenum, std::string> sources;

		const char* token = "#type";
		size_t tokenSize = strlen(token);
		size_t pos = source.find(token);
		while (pos != std::string::npos) {
			size_t eol = source.find_first_of("\r\n", pos);
			HZ_ASSERT(eol != std::string::npos, "Syntax Error");
			size_t begin = pos + tokenSize + 1;
			std::string type = source.substr(begin, eol - begin);
			HZ_ASSERT(ShaderTypeFromString(type), "Invalid Shader Type");
			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			HZ_ASSERT(nextLinePos != std::string::npos, "Syntax Error");
			pos = source.find(token, nextLinePos);
			sources[ShaderTypeFromString(type)] = source.substr(nextLinePos, (pos == std::string::npos ? source.size() - nextLinePos : pos - nextLinePos));
		}
		return sources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources) {
		HZ_PROFILE_FUNCTION();

		uint32_t program = glCreateProgram();
		std::array<GLenum, 2> glShaderIDs;
		HZ_ASSERT(shaderSources.size() <= 2, "Only support 2 shaders");

		uint32_t shaderCount = 0;
		for (const auto kv : shaderSources) {

			GLenum type = kv.first;
			std::string source = kv.second;

			GLuint shader = glCreateShader(type);

			const GLchar* sourceCstr = source.c_str();
			glShaderSource(shader, 1, &sourceCstr, 0);

			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the OpenGLShader anymore.
				glDeleteShader(shader);

				// Use the infoLog as you see fit.
				HZ_CORE_ERROR("OpenGLShader Error: {0}", infoLog.data());
				HZ_CORE_ASSERT(false, "Failed To Create Vertex OpenGLShader!");
				// In this simple program, we'll just leave
				return;
			}
			glShaderIDs[shaderCount++] = shader;
		}

		// Attach our shaders to our program
		for (auto shader : glShaderIDs) {
			glAttachShader(program, shader);
		}

		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)& isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			for (auto shader : glShaderIDs) {
				glDeleteShader(shader);
			}

			HZ_CORE_ERROR("OpenGLShader Error: {0}", infoLog.data());
			HZ_CORE_ASSERT(false, "OpenGLShader Link Error!");
			return;
		}

		// Always detach shaders after a successful link.
		for (auto shader : glShaderIDs) {
			glDetachShader(program, shader);
		}
		m_RendererID = program;
	}

	OpenGLShader::~OpenGLShader() {
		HZ_PROFILE_FUNCTION();
		glDeleteShader(m_RendererID);
	}

	void OpenGLShader::Unbind() const {
		HZ_PROFILE_FUNCTION();
		glUseProgram(0);
	}
	void OpenGLShader::Bind() const {
		HZ_PROFILE_FUNCTION();
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value) {
		HZ_PROFILE_FUNCTION();
		UploadUniformFloat3(name, value);
	}
	void OpenGLShader::SetFloat4(const std::string name, const glm::vec4& value) {
		HZ_PROFILE_FUNCTION();
		UploadUniformFloat4(name, value);
	}
	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value) {
		HZ_PROFILE_FUNCTION();
		UploadUniformMat4(name, value);
	}
	void OpenGLShader::SetInt(const std::string& name, int value){
		HZ_PROFILE_FUNCTION();
		UploadUniformInt(name, value);
	}


	uint32_t OpenGLShader::GetUniformLocation(const std::string& name) {
		int value = glGetUniformLocation(m_RendererID, name.c_str());
		HZ_ASSERT(value >= 0, "Uniform location not found");
		return value;
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value) {
		glUniform1i(GetUniformLocation(name), value);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value) {
		glUniform1f(GetUniformLocation(name), value);
	}
	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value) {
		glUniform2f(GetUniformLocation(name), value.x, value.y);
	}
	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value){
		glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);

	}
	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value){
		glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);

	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& values){
		glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(values));
	}
	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& values) {
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(values));
	}


}