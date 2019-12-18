#pragma once
#include "Hazel\Core\Window.h"
#include <GLFW\glfw3.h>

#include "Hazel\Renderer\GraphicsContext.h"


namespace Hazel {

	class HAZEL_API WindowsWindow : public Window {
	public:
		void OnUpdate() override;

		WindowsWindow(WindowProps& props);
		~WindowsWindow();
		void Init(WindowProps& props);
		void Shutdown();

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		//WindowAttributes
		virtual void ToggleCursorVisibility() override;
		virtual void SetVsync(bool enabled) override;
		inline virtual bool IsVsync() const override { return m_Data.Vsync; }
		inline virtual void SetCallbackFunc(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }

		virtual void* GetNativeWindow() override;

	private:
		GLFWwindow* m_Window;
		Scope<GraphicsContext> m_Context;

		struct WindowData {
			unsigned int Width, Height;
			std::string Title;
			bool Vsync;
			bool CursorVisible = true;
			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};

}