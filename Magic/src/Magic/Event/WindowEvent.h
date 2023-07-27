#pragma once
#include "Event.h"

namespace Magic{
	class WindowEvent : public Event
	{
	public:
		EVENT_CREATE_CLASS_CATEGORY(EventCategory::Window)
	};

	class WindowCloseEvent : public WindowEvent
	{
	public:
		EVENT_CREATE_CLASS_TYPE(EventType::WindowClose)
	};

	class WindowResizeEvent : public WindowEvent
	{
	public:
		WindowResizeEvent(int width, int height) : m_Width(width),m_Height(height){}
		int getWidth() const { return m_Width;}
		int getHeight() const {return m_Height;}

		EVENT_CREATE_CLASS_TYPE(EventType::WindowResize)
	private:
		int m_Width,m_Height;
	};

	class WindowFocusEvent : public WindowEvent
	{
	public:
		EVENT_CREATE_CLASS_TYPE(EventType::WindowFocus)
	};

	class WindowLostFocus : public WindowEvent
	{
	public:
		EVENT_CREATE_CLASS_TYPE(EventType::WindowLostFocus)
	};
}