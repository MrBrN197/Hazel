#include <Hazel.h>
#include <Hazel\Core\EntryPoint.h>

#include <glm/gtc/type_ptr.hpp>

#include <imgui\imgui.h>
#include "hzpch.h"

#include "Sandbox2D.h"

class ExampleLayer : public Hazel::Layer{
public:
	ExampleLayer()
		: m_CameraController(1280.f / 720.f, true), 
		cameraPosition(0.f),
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

		m_VertexArray = Hazel::VertexArray::Create();
		Hazel::Ref<Hazel::VertexBuffer> vertexBuffer(Hazel::VertexBuffer::Create(vertices, sizeof(vertices)));

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
		Hazel::Ref<Hazel::IndexBuffer> indexBuffer(Hazel::IndexBuffer::Create(indices, 3 * 4));
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

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec2 v_TexCoord;

void main(){
    gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1);
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
	out_color = texture(u_Texture, v_TexCoord) * vec4(vec3(u_Brightness), 1.f);
}
)";
		auto textureShader = m_ShaderLibrary.Load("TextureShader", "assets/shaders/Texture.glsl");

		m_CheckerBoardTexture = Hazel::Texture2D::Create("assets/textures/Checkerboard.png");
		m_CircleTexture = Hazel::Texture2D::Create("assets/textures/Circle.png");
		//Hazel::Ref<Hazel::OpenGLShader> textureShaderGL = std::dynamic_pointer_cast<Hazel::OpenGLShader>(textureShader);
		textureShader->SetInt("u_Texture", 0);


	}
	virtual ~ExampleLayer(){}

	virtual void OnUpdate(Hazel::Timestep ts) override {

		m_PrismRotation += 60.f * ts;

		m_CameraController.OnUpdate(ts);

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

		
		Hazel::Renderer::BeginScene(m_CameraController.GetCamera());
		
		Hazel::RenderCommand::ClearColor({0.25f, 0.65f, 0.35f, 1.f});
		Hazel::RenderCommand::Clear();

		auto textureShader = m_ShaderLibrary.Get("TextureShader");
		textureShader->Bind();
		textureShader->SetFloat4("u_Color", m_Color);

		//glm::mat4 transform = glm::translate(m_PrismPosition) * glm::rotate(glm::radians(m_PrismRotation), glm::vec3(0.0f, 1.f, 0.f));
		glm::mat4 transform = glm::mat4(1.f);
		//m_CheckerBoardTexture->Bind();
		//Hazel::Renderer::Submit(textureShader, m_VertexArray, transform);
		m_CircleTexture->Bind();
		Hazel::Renderer::Submit(textureShader, m_VertexArray, transform);
		
		Hazel::Renderer::EndScene();
	}
	virtual void OnDetach() override {}
	virtual void OnAttach() override {}
	virtual void OnImGuiRender() {
		ImGui::Begin("Settings");
		ImGui::SliderFloat4("Brightness", glm::value_ptr(m_Color), 0.f, 1.f);
		ImGui::End();
	}

	virtual void OnEvent(Hazel::Event& e) override{
		Hazel::EventDispatcher dispatcher = Hazel::EventDispatcher(e);
		dispatcher.Dispatch<Hazel::KeyPressedEvent>(HZ_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));

		m_CameraController.OnEvent(e);
	}

	bool OnKeyPressedEvent(Hazel::KeyPressedEvent& event) {
		return false;
	}

private:
	Hazel::OrthographicCameraController m_CameraController;
	Hazel::Ref<Hazel::VertexArray> m_VertexArray;
	Hazel::ShaderLibrary m_ShaderLibrary;
	Hazel::Ref<Hazel::Texture2D> m_CheckerBoardTexture;
	Hazel::Ref<Hazel::Texture2D> m_CircleTexture;

	glm::vec3 cameraPosition;
	float cameraRotation = 0.f;

	float cameraMoveSpeed = 5.f;
	float cameraRotationSpeed = 180.f;

	glm::vec3 m_PrismPosition;
	float m_ObjectSpeed = 5.f;
	float m_PrismRotation = 0.f;

	glm::vec4 m_Color = { 1.f, 1.f, 1.f, 1.f};

};



class Sandbox : public Hazel::Application {
public:
	Sandbox() : Hazel::Application() {

		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}
	~Sandbox(){}
};



Hazel::Application* Hazel::CreateApplication() {
	return new Sandbox();
}
