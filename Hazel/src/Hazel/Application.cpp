#include "hzpch.h"
#include "Application.h"
#include "Platform\Windows\WindowsWindow.h"
#include <glad\glad.h>

namespace Hazel {

	#define BIND(x) (std::bind(&Application::x, this, std::placeholders::_1))

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetCallbackFunc(BIND(OnEvent));
	}

	bool Application::OnWindowClose(WindowCloseEvent& event) {
		m_Running = false;
		return true;
	}

	void Application::OnEvent(Event& e) {
		HZ_CORE_INFO("{0}", e);

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND(OnWindowClose));

	}

	Application::~Application()
	{
		
	}

	void Application::Run() {
		
		while (m_Running) {

			glClearColor(0.25f, 0.65f, 0.35f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			m_Window->OnUpdate();
		}
	}

}