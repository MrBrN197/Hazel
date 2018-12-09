#pragma once
#include "Event.h"


namespace Hazel{

	class HAZEL_API MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(float x, float y) : m_x(x), m_y(y){

		}
		inline float GetX() { return m_x; }
		inline float GetY() { return m_y; }
		//EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		//EVENT_CLASS_TYPE(MouseMoved)
		virtual EventType GetEventType() { return EventType::AppRender; }
		virtual const char* GetName() { return ""; }
		virtual int GetCategoryFlags() { return 1; }
		//virtual std::string ToString() const { return GetName(); }



	private:
		float m_x, m_y;
	};

	class HAZEL_API MouseScrollEvent : public Event {
	public:
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		EVENT_CLASS_TYPE(MouseScrolled)
	};

	class HAZEL_API MousePressedEvent : public Event {
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class HAZEL_API MouseReleasedEvent : public Event {
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

}