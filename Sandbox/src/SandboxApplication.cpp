#include <Hazel.h>
#include <imgui\imgui.h>

class Sandbox : public Hazel::Application {
public:
	Sandbox() : Hazel::Application() {
	}

	~Sandbox(){}



};


Hazel::Application* Hazel::CreateApplication() {
	return new Sandbox();
}
