#include <Hazel.h>

class SandboxApplication : public Hazel::Application {
public:
	SandboxApplication() {
		PushLayer(new Hazel::ImGuiLayer());
	}

	~SandboxApplication(){}
};


Hazel::Application* CreateApplication() {

	return new SandboxApplication;

}
