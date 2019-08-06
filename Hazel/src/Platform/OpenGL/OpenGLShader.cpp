#include "hzpch.h"
#include "OpenGLShader.h"

#include <glad\glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Hazel {

	OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc) {

		// Read our shaders into the appropriate buffers
		// Create an empty vertex OpenGLShader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex OpenGLShader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex OpenGLShader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the OpenGLShader anymore.
			glDeleteShader(vertexShader);

			// Use the infoLog as you see fit.
			HZ_CORE_ERROR("OpenGLShader Error: {0}", infoLog.data());
			HZ_CORE_ASSERT(false, "Failed To Create Vertex OpenGLShader!");
			// In this simple program, we'll just leave
			return;
		}

		// Create an empty fragment OpenGLShader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment OpenGLShader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment OpenGLShader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the OpenGLShader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			// Use the infoLog as you see fit.
			HZ_CORE_ERROR("OpenGLShader Error: {0}", infoLog.data());
			HZ_CORE_ASSERT(false, "Failed To Create Fragment OpenGLShader!");
			// In this simple program, we'll just leave
			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_RendererID = glCreateProgram();
		uint32_t program = m_RendererID;

		// Attach our shaders to our program
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
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
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			// Use the infoLog as you see fit.
			HZ_CORE_ERROR("OpenGLShader Error: {0}", infoLog.data());
			HZ_CORE_ASSERT(false, "OpenGLShader Link Error!");
			// In this simple program, we'll just leave
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);

	}
	OpenGLShader::~OpenGLShader() {
		glDeleteShader(m_RendererID);
	}

	void OpenGLShader::Unbind() const {
		glUseProgram(0);
	}
	void OpenGLShader::Bind() const {
		glUseProgram(m_RendererID);
	}

	uint32_t OpenGLShader::GetUniformLocation(const char* name) {
		int value = glGetUniformLocation(m_RendererID, name);
		HZ_ASSERT(value >= 0, "Uniform location not found");
		return value;
	}

	void OpenGLShader::SetUniformInt(const char* name, int value) {
		glUniform1i(GetUniformLocation(name), value);
	}

	void OpenGLShader::SetUniformFloat(const char* name, float value) {
		glUniform1f(GetUniformLocation(name), value);
	}
	void OpenGLShader::SetUniformFloat2(const char* name, const glm::vec2& value) {
		glUniform2f(GetUniformLocation(name), value.x, value.y);
	}
	void OpenGLShader::SetUniformFloat3(const char* name, const glm::vec3& value){
		glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);

	}
	void OpenGLShader::SetUniformFloat4(const char* name, const glm::vec4& value){
		glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);

	}

	void OpenGLShader::SetUniformMat3(const char* name, const glm::mat3& values){
		glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(values));
	}
	void OpenGLShader::SetUniformMat4(const char* name, const glm::mat4& values) {
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(values));
	}


}