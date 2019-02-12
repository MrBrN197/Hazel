#pragma once
#include "Hazel\Core.h"
#include "../Layer.h"
#include "../Events/ApplicationEvent.h"
#include "../Events/KeyEvent.h"
#include "../Events/MouseEvent.h"

namespace Hazel {

	class HAZEL_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();

		virtual void OnUpdate() override;
		virtual void OnDetach() override;
		virtual void OnAttach() override;
		virtual void OnEvent(Event& event) override;

		inline const std::string& GetName() const { return m_DebugName; }
	private:
		bool OnMousePressedEvent(MousePressedEvent e);
		bool OnMouseReleasedEvent(MouseReleasedEvent& e);
		bool OnMouseMoved(MouseMovedEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnMouseScrolledEvent(MouseScrollEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_Time = 0.0f;
	};
}