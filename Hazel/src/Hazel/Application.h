#pragma once
#include "hzpch.h"
#include "Core.h"
#include "Window.h"
#include "Events\ApplicationEvent.h"
#include <Hazel\LayerStack.h>
#include "Hazel\ImGui\ImGuiLayer.h"
#include "Hazel\Renderer\Shader.h"

namespace Hazel {
	class HAZEL_API Application{
	public:
		Application();
		virtual ~Application();
		void OnEvent(Event& e);
		void Run();
		
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& event);
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
	private:
		static Application* s_Instance;
		LayerStack m_LayerStack;
		unsigned int m_VBO;
		unsigned int m_IBO;
		unsigned int m_VAO;
		std::unique_ptr<Shader> m_Shader;

	};

	Application* CreateApplication();
}