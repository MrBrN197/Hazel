#pragma once
#include "Event.h"


namespace Hazel{

	class HAZEL_API MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(float xpos, float ypos) : m_MouseX(xpos), m_MouseY(ypos){}

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		virtual std::string ToString() const override{ 
			std::stringstream ss;
			ss << "xPos: " << GetX() << " yPos: " << GetY(); 
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_MouseX, m_MouseY;
	};



	class HAZEL_API MouseScrollEvent : public Event {
	public:
		MouseScrollEvent(float xOffset, float yOffset) : m_xOffset(xOffset), m_yOffset(yOffset){}
		inline float GetXOffset() const { return m_xOffset; }
		inline float GetYOffset() const { return m_yOffset; }

		virtual std::string ToString() const override {
			std::stringstream ss;
			ss << "xPos: " << GetXOffset() << " yPos: " << GetYOffset();
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		EVENT_CLASS_TYPE(MouseScrolled)
	private:
		float m_xOffset, m_yOffset;
	};


	class HAZEL_API MouseButtonEvent : public Event{
	public:
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);
		int GetMouseButton() {
			return m_Button;
		}
		inline int GetMouseButton() const { return m_Button; }
	protected:
		MouseButtonEvent(int button) : m_Button(button) {}
		int m_Button;
	};

	class HAZEL_API MousePressedEvent : public MouseButtonEvent {
	public:
		MousePressedEvent(int button) : MouseButtonEvent(button) {}
		EVENT_CLASS_TYPE(MouseButtonPressed)
		std::string ToString() const override{
			std::stringstream ss;
			ss << "MouseButtonPressed: " << m_Button;
			return ss.str();
		}
	};


	class HAZEL_API MouseReleasedEvent : public MouseButtonEvent {
	public:
		MouseReleasedEvent(int button) : MouseButtonEvent(button) {}
		EVENT_CLASS_TYPE(MouseButtonReleased)
			std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonReleased: " << m_Button;
			return ss.str();
		}
	};

}