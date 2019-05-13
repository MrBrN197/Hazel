#pragma once

#include "Hazel\Renderer\GraphicsContext.h"

struct GLFWwindow;

namespace Hazel {

	class OpenGLContext : public GraphicsContext {
	public:
		OpenGLContext(GLFWwindow *window);
		virtual void Init();
		virtual void SwapBuffers();
	private:
		GLFWwindow *m_WindowHandle;
	};

}