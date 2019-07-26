#include <Hazel.h>
#include <imgui\imgui.h>
#include "hzpch.h"


class ExampleLayer : public Hazel::Layer{
public:
	ExampleLayer()
		: m_Camera(
			60.f,
			Hazel::Application::Get().GetWindow().GetWidth(),
			Hazel::Application::Get().GetWindow().GetHeight(),
			1.f,
			6.f),
		m_CameraPosition(0.f),
		Hazel::Layer() {

		float vertices[7 * 5] = {
			-0.5f, -0.5f,  0.5f, 0.2f, 0.6f, 0.9f, 1.0f,
			 0.5f, -0.5f,  0.5f, 0.8f, 0.7f, 0.2f, 1.0f,
			 0.0f,  0.5f,  0.0f, 0.2f, 0.8f, 0.2f, 1.0f,
			 0.5f, -0.5f, -0.5f, 0.2f, 0.8f, 0.2f, 1.0f,
			-0.5f, -0.5f, -0.5f, 0.5f, 0.1f, 0.2f, 1.0f
		};

		m_VertexArray.reset(Hazel::VertexArray::Create());
		std::shared_ptr<Hazel::VertexBuffer> vertexBuffer(Hazel::VertexBuffer::Create(vertices, sizeof(vertices)));

		uint32_t indices[3 * 4] = {
			0, 1, 2,
			1, 3, 2,
			4, 0, 2,
			3, 4, 2
		};
		std::shared_ptr<Hazel::IndexBuffer> indexBuffer(Hazel::IndexBuffer::Create(indices, 3 * 4));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		Hazel::BufferLayout layout({
			{Hazel::ShaderDataType::Float3, "a_Position"},
			{Hazel::ShaderDataType::Float4, "a_Color"}
			});
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);


		std::string vertexSrc = R"(
#version 330 core
layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec4 a_Color;

uniform mat4 a_ViewProjeciton;

out vec4 v_Color;

void main(){
    gl_Position = a_ViewProjeciton * vec4(a_Position, 1);
	v_Color = a_Color;
}
)";
		std::string fragmentSrc = R"(
#version 330 core
in vec4 v_Color;

out vec4 out_color;
void main(){
	out_color = v_Color;
}
)";

		m_Shader.reset(new Hazel::Shader(vertexSrc, fragmentSrc));

	}
	virtual ~ExampleLayer(){}

	virtual void OnUpdate() override {
		Hazel::Renderer::BeginScene(m_Camera);

		Hazel::Renderer::Submit(m_Shader, m_VertexArray);
		Hazel::Renderer::EndScene();

	}
	virtual void OnDetach() override {
	}
	virtual void OnAttach() override {}
	virtual void OnImGuiRender() {}
	virtual void OnEvent(Hazel::Event& event) override{
		Hazel::EventDispatcher dispatcher = Hazel::EventDispatcher(event);
		dispatcher.Dispatch<Hazel::KeyPressedEvent>(HZ_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
	}

	bool OnKeyPressedEvent(Hazel::KeyPressedEvent& event) {

		if (event.GetKeyCode() == HZ_KEY_LEFT) {
			m_CameraPosition.x += m_CameraMoveSpeed;
		}
		else if (event.GetKeyCode() == HZ_KEY_RIGHT) {
			m_CameraPosition.x -= m_CameraMoveSpeed;
		}
		if (event.GetKeyCode() == HZ_KEY_UP) {
			m_CameraPosition.y += m_CameraMoveSpeed;
		}
		else if (event.GetKeyCode() == HZ_KEY_DOWN) {
			m_CameraPosition.y -= m_CameraMoveSpeed;
		}
		return false;
	}


private:
	Hazel::PerspectiveCamera m_Camera;
	std::shared_ptr<Hazel::VertexArray> m_VertexArray;
	std::shared_ptr<Hazel::Shader> m_Shader;

	glm::vec3 m_CameraPosition;
	float m_CameraRotation;

	float m_CameraMoveSpeed = 0.1f;
	float m_CameraRotationSpeed = 2.f;
};



class Sandbox : public Hazel::Application {
public:
	Sandbox() : Hazel::Application() {

		PushLayer(new ExampleLayer());
	}
	~Sandbox(){}
};



Hazel::Application* Hazel::CreateApplication() {
	return new Sandbox();
}
