#pragma once

#include "Hazel/Renderer/PerspectiveCamera.h"

namespace Hazel {

	class Renderer3D{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const PerspectiveCamera& camera);
		static void EndScene();

		static void DrawCube(glm::vec3 position, glm::vec4 color);
		static void DrawFloor();
		static void DrawCubeMesh(glm::vec3 position, glm::vec4 color);
	};

}