#include "hzpch.h"
#include "Application.h"
#include "Platform\Windows\WindowsWindow.h"
#include "Hazel\Renderer\Buffer.h"
#include "Hazel\Renderer\RenderCommand.h"
#include "Hazel\Renderer\Renderer.h"
#include "Hazel\Renderer\PerspectiveCamera.h"
#include "Hazel\Core\Input.h"

namespace Hazel {

	#define BIND_EVENT_FN(x) (std::bind(&Application::x, this, std::placeholders::_1))

	Application* Application::s_Instance = nullptr;

	Application::Application(){
		s_Instance = this;
		m_Window = Scope<Window>(Window::Create());
		m_ImGuiLayer = new ImGuiLayer;
		PushOverlay(m_ImGuiLayer);
		m_Window->SetCallbackFunc(BIND_EVENT_FN(OnEvent));

		Renderer::Init();

	}
	Application::~Application()	{
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
	}
	void Application::PushOverlay(Layer* layer) {
		m_LayerStack.PushOverlay(layer);
	}
	void Application::PopLayer(Layer* layer){
		m_LayerStack.PopLayer(layer);
	}
	void Application::PopOverlay(Layer* layer) {
		m_LayerStack.PopOverlay(layer);
	}

	void Application::OnEvent(Event& e) {

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.m_Handled)
				break;
		}
	}

	void Application::Run() {

		while (m_Running) {

			float time = (float)glfwGetTime();
			Timestep ts = time - m_LastFrameTime;
			m_LastFrameTime = time;

			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate(ts);
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();


			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e) {
		if (e.GetHeight() == 0 || e.GetWidth() == 0) {
			m_Minimized = false;
			return false;
		}

		m_Minimized = true;

		Renderer::OnWindowResize((uint32_t)e.GetWidth(), (uint32_t)e.GetHeight());

		return false;
	}


}