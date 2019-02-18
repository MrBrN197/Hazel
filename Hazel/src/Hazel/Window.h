#pragma once
#include "Events\Event.h"
#include "Core.h"

namespace Hazel {

	struct WindowProps {
		unsigned int Width, Height;
		std::string Title;
		bool Vsync;
		WindowProps(unsigned int width = 1280, unsigned int height = 720, const std::string& title = "Hazel", bool vsync = true)
			: Width(width), Height(height), Title(title), Vsync(vsync) {}
	};

	class HAZEL_API Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window(){}

		virtual void OnUpdate() = 0; 

		inline virtual unsigned int GetWidth() const = 0;
		inline virtual unsigned int GetHeight() const = 0;

		//WindowAttributes
		virtual void SetVsync(bool enabled) = 0;
		inline virtual bool IsVsync() const = 0;
		inline virtual void SetCallbackFunc(const EventCallbackFn& callback) = 0;

		virtual void* GetNativeWindow() = 0;

		static Window* Create(WindowProps& props = WindowProps());
	};
}