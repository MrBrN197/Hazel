#include <Hazel.h>

class SandboxApplication : public Hazel::Application {};


Hazel::Application* CreateApplication() {

	return new Hazel::Application;

}
