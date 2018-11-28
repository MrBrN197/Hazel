#include <Hazel.h>

class SandboxApplication : public Hazel::Application {
public:
	void Run() {
		Hazel::Log::getClientLogger()->info("App Initialized");
		while (true);
	}
};

Hazel::Application* CreateApplication() {
	return new SandboxApplication;
}