#pragma once
#include "Hazel\Window.h"
#include <GLFW\glfw3.h>

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
		void SetVsync(bool enabled) override;
		inline bool IsVsync() const override { return m_Data.Vsync; }
		inline void SetCallbackFunc(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }

	private:
		GLFWwindow* m_Window;
	public:
		struct WindowData {
			unsigned int Width, Height;
			std::string Title;
			bool Vsync;
			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};

}