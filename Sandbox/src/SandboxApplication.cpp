#include <Hazel.h>

class SandboxApplication : public Hazel::Application {
public:

};

Hazel::Application* CreateApplication() {
	return new SandboxApplication;
}