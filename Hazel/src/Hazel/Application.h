#pragma once
#include "hzpch.h"
#include "Core.h"
#include "Window.h"
#include "Events\ApplicationEvent.h"
#include <Hazel\LayerStack.h>

namespace Hazel {
	class HAZEL_API Application{
	public:
		Application();
		virtual ~Application();
		void OnEvent(Event& e);
		virtual void Run();
		
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& event);
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	private:
		static Application* s_Instance;
		LayerStack m_LayerStack;
	};

	Application* CreateApplication();
}