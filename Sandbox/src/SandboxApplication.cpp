#include <Hazel.h>
#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/gtc/type_ptr.hpp>

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
		Hazel::Layer(), 
		m_PrismPosition({0.f, 0.f, -2.f}) {

		//float vertices[7 * 5] = {
		//	-0.5f, -0.5f,  0.5f, 0.2f, 0.6f,
		//	 0.5f, -0.5f,  0.5f, 0.8f, 0.7f,
		//	 0.0f,  0.5f,  0.0f, 0.2f, 0.8f,
		//	 0.5f, -0.5f, -0.5f, 0.2f, 0.8f,
		//	-0.5f, -0.5f, -0.5f, 0.5f, 0.1f,
		//};
		float vertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		m_VertexArray.reset(Hazel::VertexArray::Create());
		std::shared_ptr<Hazel::VertexBuffer> vertexBuffer(Hazel::VertexBuffer::Create(vertices, sizeof(vertices)));

		//uint32_t indices[3 * 4] = {
		//	0, 1, 2,
		//	1, 3, 2,
		//	4, 0, 2,
		//	3, 4, 2
		//};
		uint32_t indices[3 * 2] = {
			0, 1, 2,
			0, 2, 3
		};
		std::shared_ptr<Hazel::IndexBuffer> indexBuffer(Hazel::IndexBuffer::Create(indices, 3 * 4));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		Hazel::BufferLayout layout({
			{Hazel::ShaderDataType::Float3, "a_Position"},
			{Hazel::ShaderDataType::Float2, "a_TexCoord"}
			});
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);


		std::string vertexSrc = R"(
#version 330 core
layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec2 a_TexCoord;

uniform mat4 u_ViewProjeciton;
uniform mat4 u_Transform;

out vec2 v_TexCoord;

void main(){
    gl_Position = u_ViewProjeciton * u_Transform * vec4(a_Position, 1);
	v_TexCoord = a_TexCoord;
}
)";
		std::string fragmentSrc = R"(
#version 330 core

layout(location = 0) out vec4 out_color;

in vec2 v_TexCoord;

uniform float u_Brightness;
uniform sampler2D u_Texture;

void main(){
	out_color = texture(u_Texture, v_TexCoord) * u_Brightness;
}
)";

		m_Shader.reset(Hazel::Shader::Create(vertexSrc, fragmentSrc));

		m_Texture = Hazel::Texture2D::Create("assets/textures/Checkerboard.png");
		m_Texture->Bind();
		//std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_Shader)->Bind();
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_Shader)->SetUniformInt("u_Texture", 0);


	}
	virtual ~ExampleLayer(){}

	virtual void OnUpdate(Hazel::Timestep ts) override {

		m_PrismRotation += 60.f * ts;

		if (Hazel::Input::IsKeyPressed(HZ_KEY_LEFT)) {
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		}
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_RIGHT)) {
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		}
		if (Hazel::Input::IsKeyPressed(HZ_KEY_DOWN)) {
			m_CameraPosition.z += m_CameraMoveSpeed * ts;
		}
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_UP)) {
			m_CameraPosition.z -= m_CameraMoveSpeed * ts;
		}

		if (Hazel::Input::IsKeyPressed(HZ_KEY_J)) {
			m_PrismPosition.x -= m_ObjectSpeed * ts;
		}
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_L)) {
			m_PrismPosition.x += m_ObjectSpeed * ts;
		}
		if (Hazel::Input::IsKeyPressed(HZ_KEY_I)) {
			m_PrismPosition.z -= m_ObjectSpeed * ts;
		}
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_K)) {
			m_PrismPosition.z += m_ObjectSpeed * ts;
		}

		if (Hazel::Input::IsKeyPressed(HZ_KEY_A)) {
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		}
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_D)) {
			m_CameraRotation += m_CameraRotationSpeed * ts;
		}


		Hazel::RenderCommand::EnableDepthTesting();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);
		Hazel::Renderer::BeginScene(m_Camera);
		
		Hazel::RenderCommand::ClearColor({0.25f, 0.65f, 0.35f, 1.f});
		Hazel::RenderCommand::Clear();

		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_Shader)->Bind();
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_Shader)->SetUniformFloat("u_Brightness", m_Brightness);

		glm::mat4 transform = glm::translate(m_PrismPosition) * glm::rotate(glm::radians(m_PrismRotation), glm::vec3(0.0f, 1.f, 0.f));
		Hazel::Renderer::Submit(m_Shader, m_VertexArray, transform);
		
		Hazel::Renderer::EndScene();
	}
	virtual void OnDetach() override {
	}
	virtual void OnAttach() override {}
	virtual void OnImGuiRender() {
		ImGui::Begin("Settings");
		ImGui::SliderFloat("Brightness", &m_Brightness, 0.f, 1.f);
		ImGui::End();
	}

	virtual void OnEvent(Hazel::Event& event) override{
		Hazel::EventDispatcher dispatcher = Hazel::EventDispatcher(event);
		dispatcher.Dispatch<Hazel::KeyPressedEvent>(HZ_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
	}

	bool OnKeyPressedEvent(Hazel::KeyPressedEvent& event) {
		return false;
	}

private:
	Hazel::PerspectiveCamera m_Camera;
	Hazel::Ref<Hazel::VertexArray> m_VertexArray;
	Hazel::Ref<Hazel::Shader> m_Shader;
	Hazel::Ref<Hazel::Texture2D> m_Texture;

	glm::vec3 m_CameraPosition;
	float m_CameraRotation = 0.f;

	float m_CameraMoveSpeed = 5.f;
	float m_CameraRotationSpeed = 180.f;

	glm::vec3 m_PrismPosition;
	float m_ObjectSpeed = 5.f;
	float m_PrismRotation = 0.f;

	float m_Brightness = 1.f;

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
