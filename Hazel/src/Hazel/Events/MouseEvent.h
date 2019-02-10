#pragma once
#include "Event.h"


namespace Hazel{

	class HAZEL_API MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(float xpos, float ypos) : m_xPos(xpos), m_yPos(ypos){}
		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		virtual std::string ToString() const override{ 
			std::stringstream ss;
			ss << "xPos: " << GetX() << " yPos: " << GetY(); 
			return ss.str();
		}
		inline float GetX() const { return m_xPos; }
		inline float GetY() const { return m_yPos; }
	private:
		float m_xPos, m_yPos;
	};



	class HAZEL_API MouseScrollEvent : public Event {
	public:
		MouseScrollEvent(float xOffset, float yOffset) : m_xOffset(xOffset), m_yOffset(yOffset){}
		virtual std::string ToString() const override {
			std::stringstream ss;
			ss << "xPos: " << GetX() << " yPos: " << GetY();
			return ss.str();
		}
		inline float GetX() const { return m_xOffset; }
		inline float GetY() const { return m_yOffset; }
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		EVENT_CLASS_TYPE(MouseScrolled)
	private:
		float m_xOffset, m_yOffset;
	};


	class HAZEL_API MousePressedEvent : public Event {
	public:
		MousePressedEvent(int button) : m_button(button) {}
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		EVENT_CLASS_TYPE(MouseButtonPressed)
	private:
		int m_button;
	};


	class HAZEL_API MouseReleasedEvent : public Event {
	public:
		MouseReleasedEvent(int button) : m_button(button) {}
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		EVENT_CLASS_TYPE(MouseButtonReleased)
	private:
		int m_button;
	};

}