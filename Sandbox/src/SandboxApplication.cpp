#include "SanboxApplication.h"
#include <stdio.h>

TestApplication::TestApplication() {}
TestApplication::~TestApplication() {}
void TestApplication::Run(){
	printf("Hello, Hazel!");
	while (true) {
	}
}

Hazel::Application* GetApplication() {
	Hazel::Application *application = new TestApplication();
	return application;
}
