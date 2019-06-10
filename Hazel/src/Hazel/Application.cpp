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

		float vertices[9] = {
			-0.5f, -0.5f, 0.f,
			 0.5f, -0.5f, 0.f,
			-0.0f, +0.5f, 0.f
		};
		unsigned short indices[3] = { 0,1,2 };

		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glGenBuffers(1, &m_IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 3, (const void*)0);


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

			glBindVertexArray(m_VAO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);

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