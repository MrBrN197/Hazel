#include "hzpch.h"
#include "Application.h"
#include "Platform\Windows\WindowsWindow.h"
#include <glad\glad.h>

namespace Hazel {

	#define BIND_EVENT_FN(x) (std::bind(&Application::x, this, std::placeholders::_1))

	Application* Application::s_Instance = nullptr;

	Application::Application(){
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_ImGuiLayer = new ImGuiLayer;
		PushOverlay(m_ImGuiLayer);
		m_Window->SetCallbackFunc(BIND_EVENT_FN(OnEvent));
	}
	Application::~Application()	{
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	void Application::PushOverlay(Layer* layer) {
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}
	void Application::PopLayer(Layer* layer){
		m_LayerStack.PopLayer(layer);
		layer->OnDetach();
	}
	void Application::PopOverlay(Layer* layer) {
		m_LayerStack.PopOverlay(layer);
		layer->OnDetach();
	}

	bool Application::OnWindowClose(WindowCloseEvent& event) {
		m_Running = false;
		return true;
	}
	void Application::OnEvent(Event& e) {

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);
		}

	}

	void Application::Run() {

		while (m_Running) {

			glClearColor(0.25f, 0.65f, 0.35f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();


			m_Window->OnUpdate();
		}
	}

}