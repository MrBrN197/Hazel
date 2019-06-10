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

		HZ_CORE_INFO(" Vendor: {0}", glGetString(GL_VENDOR));
		HZ_CORE_INFO(" Renderer: {0}", glGetString(GL_RENDERER));
		HZ_CORE_INFO(" Vendor: {0}", glGetString(GL_VERSION));

	}
	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(m_WindowHandle);
	}

}