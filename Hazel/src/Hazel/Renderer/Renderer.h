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
		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.f));
	private:
		struct SceneData {
			glm::mat4 viewProjection;
		};
		static SceneData s_SceneData;
	};


}