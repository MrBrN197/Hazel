#pragma once
#include <iostream>

int main(int argc, char* argv[]) {

	Hazel::Log::Init();

	Hazel::Application* app = Hazel::CreateApplication();
	app->Run();
	delete app;

}
