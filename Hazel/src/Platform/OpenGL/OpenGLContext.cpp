#include "hzpch.h"

#include "OpenGLContext.h"

#include <GLFW\glfw3.h>
#include <glad\glad.h>

namespace Hazel {

	OpenGLContext::OpenGLContext(GLFWwindow *window)
		: m_WindowHandle(window) {
		HZ_ASSERT(window, "Window handle is null!");
		
	}
	void OpenGLContext::Init() {

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HZ_CORE_ASSERT(status, "Failed to initialize glad");
	}
	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(m_WindowHandle);
	}

}