#pragma once
#include <glm/glm.hpp>

#include <string>
#include <unordered_map>

namespace Hazel {

	class Shader {
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
		virtual void SetFloat4(const std::string name, const glm::vec4& value) = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;
		virtual void SetInt(const std::string& name, int value) = 0;

		virtual const std::string& GetName() const = 0;

		static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		static Ref<Shader> Create(const std::string& path);
	};

	class ShaderLibrary {
	public:
		Ref<Shader> Load(const std::string& filepath);
		Ref<Shader> Load(const std::string& name, const std::string& filepath);
		void Add(const std::string& name, Ref<Shader>& shader);
		void Add(Ref<Shader>& shader);
	
		Ref<Shader> Get(const std::string& name);
	
	private:
		bool Exists(const std::string& name) {
			return m_Shaders.find(name) != m_Shaders.end();
		}
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	
	};

}