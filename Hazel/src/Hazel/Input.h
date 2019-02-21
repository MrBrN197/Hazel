#pragma once
#include "Hazel\Core.h"

namespace Hazel {


	class HAZEL_API Input {
	public:
		static bool IsMouseButtonPressed(int button) {return s_Instance->IsMouseButtonPressedImpl(button); }
		static bool IsKeyPressed(int keycode) {return s_Instance->IsKeyPressedImpl(keycode);}
		static std::pair<float, float> GetMousePosition() {return s_Instance->GetMousePositionImpl();}
		static float GetMouseX() {return s_Instance->GetMouseXImpl();}
		static float GetMouseY() {return s_Instance->GetMouseYImpl();}
	protected:
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
	protected:
		static Input* s_Instance;

	};

}