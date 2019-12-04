#pragma once
#include "Core.h"

#include "Window.h"
#include "Hazel\Core\LayerStack.h"
#include "Hazel\Events\ApplicationEvent.h"

#include "Hazel\ImGui\ImGuiLayer.h"

#include "Hazel\Renderer\Shader.h"
#include "Hazel\Renderer\Buffer.h"
#include "Hazel\Renderer\VertexArray.h"

#include "Hazel\Core\Timestep.h"

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
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.f;
	private:
		static Application* s_Instance;
	};

	Application* CreateApplication();
}