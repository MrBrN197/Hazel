#include "Hazel\Core\Input.h"

namespace Hazel {
	class HAZEL_API WindowsInput : public Input{
	

		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual bool IsKeyPressedImpl(int keycode) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;

		virtual void SetMouseXImpl(float x) override;

	};
}