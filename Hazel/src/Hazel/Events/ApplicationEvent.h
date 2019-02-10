#include "Event.h"

namespace Hazel {
	
	class HAZEL_API WindowResizeEvent : public Event {
	public:
		WindowResizeEvent(float width, float height) : m_Width(width) , m_Height(height){}
		inline float GetWidth() const { return m_Width; }
		inline float GetHeight() const { return m_Height; }
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(WindowResize)
		std::string ToString() const override {
			std::stringstream ss;
			ss << "Width: " << GetWidth() << " Height: " << GetHeight() << std::endl;
			return ss.str();
		}
	private:
		float m_Width, m_Height;
	};

	class HAZEL_API WindowCloseEvent : public Event {
	public:
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(WindowClose)
	};
	
	class HAZEL_API WindowMovedEvent : public Event{
	public:
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(WindowMoved)
	};
	
	class HAZEL_API WindowTickEvent : public Event {
	public:
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(AppTick)
	};
	class HAZEL_API WindowUpdateEvent : public Event {
	public:
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(AppUpdate)
	};
	
	class HAZEL_API WindowRenderEvent : public Event {
	public:
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(AppRender)
	};

}