#include "hzpch.h"
#include "Application.h"
#include "Platform/Windows/WindowsWindow.h"
#include "Hazel/Renderer/Buffer.h"
#include "Hazel/Renderer/RenderCommand.h"
#include "Hazel/Renderer/Renderer.h"

namespace Hazel {

	#define BIND_EVENT_FN(x) (std::bind(&Application::x, this, std::placeholders::_1))

	Application* Application::s_Instance = nullptr;

	Application::Application(){
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_ImGuiLayer = new ImGuiLayer;
		PushOverlay(m_ImGuiLayer);
		m_Window->SetCallbackFunc(BIND_EVENT_FN(OnEvent));


		float vertices[7 * 3] = {
			-0.5f, -0.5f, 0.f, 0.2f, 0.6f, 0.9f, 1.0f,
			 0.5f, -0.5f, 0.f, 0.8f, 0.7f, 0.2f, 1.0f,
			 0.f,   0.5f, 0.f, 0.2f, 0.8f, 0.2f, 1.0f
		};

		m_VertexArray.reset(VertexArray::Create());
		std::shared_ptr<VertexBuffer> vertexBuffer(VertexBuffer::Create(vertices, sizeof(vertices)));

		uint32_t indices[3] = { 0,1,2 };
		std::shared_ptr<IndexBuffer> indexBuffer(IndexBuffer::Create(indices, 3));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		BufferLayout layout({
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"}
			});
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);


		std::string vertexSrc = R"(
#version 330 core
layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec4 a_Color;

out vec3 v_Position;
out vec4 v_Color;

void main(){
    gl_Position = vec4(a_Position, 1.0);
    v_Position = a_Position;
	v_Color = a_Color;
}
)";
		std::string fragmentSrc = R"(
#version 330 core
in vec3 v_Position;
in vec4 v_Color;
out vec4 out_color;
void main(){
	out_color = v_Color;
}
)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));

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

			RenderCommand::Clear();
			RenderCommand::ClearColor({ 0.25f, 0.65f, 0.35f, 1.0f });

			Renderer::BeginScene();

			m_Shader->Bind();
			Renderer::Submit(m_VertexArray);

			Renderer::EndScene();

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