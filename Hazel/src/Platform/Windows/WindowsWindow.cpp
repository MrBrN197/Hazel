#include "hzpch.h"
#include "WindowsWindow.h"
#include "Hazel\Events\ApplicationEvent.h"
#include "Hazel\Events\MouseEvent.h"
#include "Hazel\Events\KeyEvent.h"
#include <glad\glad.h>

namespace Hazel {

	static bool s_GlfwInitialized = false;

	Window* Window::Create(WindowProps& props){
		return new WindowsWindow(props);
	}

	void WindowsWindow::Init(WindowProps& props) {
		m_Data.Title = props.Title;
		m_Data.Height = props.Height;
		m_Data.Width = props.Width;
		m_Data.Vsync = props.Vsync;

		if (!s_GlfwInitialized) {
			int success = glfwInit();
			HZ_CORE_ASSERT(success, "Failed To Initialize GLFW");
			s_GlfwInitialized = true;
		}

		m_Window = glfwCreateWindow(props.Width, props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HZ_CORE_ASSERT(status, "Failed to initialize glad");

		glfwSetWindowUserPointer(m_Window, &this->m_Data);
		//GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			WindowResizeEvent event((float)width, (float)height);

			WindowData& windowsWindow = *(WindowData*)glfwGetWindowUserPointer(window);
			windowsWindow.Height = height;
			windowsWindow.Width = width;

			windowsWindow.EventCallback(event);
		});
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {

			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS: {
				KeyPressedEvent event(scancode, 0);
				data.EventCallback(event);
				break;
			}
			case GLFW_REPEAT: {
				KeyPressedEvent event(scancode, 1);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE: {
				KeyReleasedEvent event(scancode);
				data.EventCallback(event);
				break;
			}
			}
		});
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {

			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS: {
				MousePressedEvent event(button);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE: {
				MouseReleasedEvent event(button);
				data.EventCallback(event);
				break;
			}
			}
		});
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrollEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {

			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);

		});
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent event(keycode);
			data.EventCallback(event);
		});

	}
	void WindowsWindow::Shutdown() {
		glfwDestroyWindow(m_Window);
	}
	WindowsWindow::WindowsWindow(WindowProps& props) {
		Init(props);
	}
	WindowsWindow::~WindowsWindow() {
		Shutdown();
	}

	void WindowsWindow::OnUpdate(){
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

	void WindowsWindow::SetVsync(bool enabled) {
		if (enabled) {
			glfwSwapInterval(1);
		}
		else {
			glfwSwapInterval(0);
		}
		m_Data.Vsync = enabled;
	}

	void* WindowsWindow::GetNativeWindow() {
		return m_Window;
	}
	
}