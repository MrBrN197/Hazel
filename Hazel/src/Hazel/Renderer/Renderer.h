#pragma once
#include "Hazel/Renderer/VertexArray.h"
#include "Hazel/Renderer/RendererAPI.h"
#include "Hazel/Renderer/PerspectiveCamera.h"
#include "Hazel/Renderer/Shader.h"

namespace Hazel {

	class Renderer {
	public:
		static void BeginScene(PerspectiveCamera camera);
		static void EndScene();
		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);
	private:
		struct SceneData {
			glm::mat4 viewProjection;
		};
		static SceneData s_SceneData;
	};


}