#pragma once
#include <iostream>

extern Hazel::Application* CreateApplication();

int main(int argc, char* argv[]) {

	Hazel::Log::Init();

	Hazel::Application* app = CreateApplication();
	app->Run();
	delete app;

}
