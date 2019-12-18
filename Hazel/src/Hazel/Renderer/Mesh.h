#pragma once

#include "hzpch.h"

#include <glm/glm.hpp>

namespace Hazel {
	class Mesh {
	public:
		Mesh(const std::string& path);
		~Mesh() = default;
		
		std::vector<glm::vec3> m_Vertices;
		std::vector<glm::vec3> m_Normals;
		std::vector<glm::vec2> m_TexCoords;
		std::vector<uint32_t> m_Indices;
	};
}