#pragma once
#include <glm/glm.hpp>

namespace Hazel {

	class Shader {
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;
		inline uint32_t GetRendererID() const { return  m_RendererID; }
		uint32_t GetUniformLocation(const char* name);
		void SetUniformMat4(const char* name, const glm::mat4& values);
	private:
		uint32_t m_RendererID;
	};

}