#pragma once
#include "Hazel/Renderer/VertexArray.h"
#include "Hazel/Renderer/RendererAPI.h"
#include "Hazel/Renderer/PerspectiveCamera.h"
#include "Hazel/Renderer/OrthographicCamera.h"
#include "Hazel/Renderer/Shader.h"

namespace Hazel {

	class Renderer {
	public:
		static void Init();
		static void OnWindowResize(uint32_t width, uint32_t height);
		static void BeginScene(PerspectiveCamera camera);
		static void BeginScene(OrthographicCamera camera);
		static void EndScene();
		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.f));
	private:
		struct SceneData {
			glm::mat4 viewProjection;
		};
		static Scope<SceneData> s_SceneData;
	};


}