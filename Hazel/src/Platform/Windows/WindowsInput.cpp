#include "hzpch.h"
#include "WindowsInput.h"
#include "Hazel\Core\Application.h"
#include <GLFW\glfw3.h>

namespace Hazel {

	Scope<Input> WindowsInput::s_Instance = CreateScope<WindowsInput>();

	bool WindowsInput::IsMouseButtonPressedImpl(int button) {
	
		GLFWwindow* window = (GLFWwindow*)Application::Get().GetWindow().GetNativeWindow();
		int state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;

	}

	bool WindowsInput::IsKeyPressedImpl(int keycode) {
		GLFWwindow* window = (GLFWwindow*)Application::Get().GetWindow().GetNativeWindow();
		int state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS  || state == GLFW_REPEAT;
	}


	std::pair<float, float> WindowsInput::GetMousePositionImpl() {
		
		GLFWwindow* window = (GLFWwindow*)Application::Get().GetWindow().GetNativeWindow();
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return { (float)x, (float)y };
	}
	
	float WindowsInput::GetMouseXImpl() {
		auto [x, y] = GetMousePositionImpl();
		return x;
	}
	float WindowsInput::GetMouseYImpl() {
		auto [x, y] = GetMousePositionImpl();
		return y;
	}

	void WindowsInput::SetMouseXImpl(float x) {
		glfwSetCursorPos((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow(), x, GetMouseYImpl());
	}

}