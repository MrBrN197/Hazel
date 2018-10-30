#pragma once 
#include "Application.h"

extern Hazel::Application* GetApplication();

int main(int argc, char* argv[]) {

	Hazel::Application *application = GetApplication();
	application->Run();
	delete application;

}