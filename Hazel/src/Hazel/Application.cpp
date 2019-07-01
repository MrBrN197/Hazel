#include "hzpch.h"
#include "Application.h"
#include "Platform\Windows\WindowsWindow.h"
#include <glad\glad.h>
#include "Hazel\Renderer\Buffer.h"

namespace Hazel {

	#define BIND_EVENT_FN(x) (std::bind(&Application::x, this, std::placeholders::_1))

	Application* Application::s_Instance = nullptr;

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
		switch (type)
		{
			case ShaderDataType::Float:	 return GL_FLOAT;
			case ShaderDataType::Float2: return GL_FLOAT;
			case ShaderDataType::Float3: return GL_FLOAT;
			case ShaderDataType::Float4: return GL_FLOAT;
			case ShaderDataType::Mat3:	 return GL_FLOAT;
			case ShaderDataType::Mat4:	 return GL_FLOAT;
			case ShaderDataType::Int:	 return GL_INT;
			case ShaderDataType::Int2:	 return GL_INT;
			case ShaderDataType::Int3:	 return GL_INT;
			case ShaderDataType::Int4:	 return GL_INT;
			case ShaderDataType::Bool:	 return GL_BOOL;
		}
		HZ_CORE_ASSERT(false, "Unknown ShaderDataType");
		return GL_NONE;
	}

	Application::Application(){
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_ImGuiLayer = new ImGuiLayer;
		PushOverlay(m_ImGuiLayer);
		m_Window->SetCallbackFunc(BIND_EVENT_FN(OnEvent));

		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		float vertices[7 * 3] = {
			-0.5f, -0.5f, 0.f, 0.2f, 0.6f, 0.9f, 1.0f,
			 0.5f, -0.5f, 0.f, 0.8f, 0.7f, 0.2f, 1.0f,
			 0.f,   0.5f, 0.f, 0.2f, 0.8f, 0.2f, 1.0f
		};
		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		uint32_t indices[3] = { 0,1,2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, 3));


		BufferLayout layout({
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"}
			});
		m_VertexBuffer->SetLayout(layout);
		uint32_t index = 0;
		for (auto element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				BufferElement::GetComponentCount(element.Type),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				(element.Normalized) ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			index++;
		}


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

			glClearColor(0.25f, 0.65f, 0.35f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


			glBindVertexArray(m_VAO);
			m_Shader->Bind();
			m_VertexBuffer->Bind();
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, 0);

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