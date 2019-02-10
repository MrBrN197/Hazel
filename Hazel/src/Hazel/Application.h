#pragma once
#include "hzpch.h"
#include "Core.h"
#include "Window.h"
#include "Events\ApplicationEvent.h"

namespace Hazel {
	class HAZEL_API Application{
	public:
		Application();
		virtual ~Application();
		void OnEvent(Event& e);
		virtual void Run();
	private:
		bool OnWindowClose(WindowCloseEvent& event);
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	Application* CreateApplication();
}