#pragma once

#include "Hazel/Renderer/PerspectiveCamera.h"
#include "Hazel/Renderer/Mesh.h"

namespace Hazel {

	class Renderer3D{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const PerspectiveCamera& camera);
		static void EndScene();

		static void DrawCube(const glm::vec3& position, const glm::vec4& color);
		static void DrawFloor();
		static void Submit(const Mesh& mesh);
		static void Flush();
	};

}