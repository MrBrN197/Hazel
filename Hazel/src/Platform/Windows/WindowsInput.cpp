#include "hzpch.h"
#include "WindowsInput.h"
#include "Hazel\Application.h"
#include <GLFW\glfw3.h>

namespace Hazel {

	Input* WindowsInput::s_Instance = new WindowsInput;

	bool WindowsInput::IsMouseButtonPressedImpl(int button) {
	
		GLFWwindow* window = (GLFWwindow*)Application::Get().GetWindow().GetNativeWindow();
		int state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;

	}

	bool WindowsInput::IsKeyPressedImpl(int keycode) {
		GLFWwindow* window = (GLFWwindow*)Application::Get().GetWindow().GetNativeWindow();
		int state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || GLFW_REPEAT;
	}


	std::pair<float, float> WindowsInput::GetMousePositionImpl() {
		
		GLFWwindow* window = (GLFWwindow*)Application::Get().GetWindow().GetNativeWindow();
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return { (float)x, (float)y };
	}
	

	float WindowsInput::GetMouseXImpl() {
		
		std::pair<float,float> xy = GetMousePositionImpl();
		return std::get<0>(xy);

	}
	float WindowsInput::GetMouseYImpl() {
		std::pair<float, float> xy = GetMousePositionImpl();
		return std::get<1>(xy);
	}

}