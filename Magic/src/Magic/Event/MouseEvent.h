#pragma once
#include "Event.h"

namespace Magic {
	class MouseMoveEvent : public Event
	{
	public:
		MouseMoveEvent(const float x, const float y) : m_MouseX(x), m_MouseY(y){}

		float GetX() const { return m_MouseX; }
		float GetY() const { return m_MouseY; }

		EVENT_CREATE_CLASS_CATEGORY(EventCategory::Input | EventCategory::Mouse)
		EVENT_CREATE_CLASS_TYPE(EventType::MouseMove)
	private:
		float m_MouseX,m_MouseY;
	};

	class MouseScrollEvent : public Event
	{
	public:
		MouseScrollEvent(const float x, const float y) : m_DeltaX(x), m_DeltaY(y) {}
		float GetDeltaX() const { return m_DeltaX; }
		float GetDeltaY() const { return m_DeltaY; }

		EVENT_CREATE_CLASS_CATEGORY(EventCategory::Input | EventCategory::Mouse)
		EVENT_CREATE_CLASS_TYPE(EventType::MouseScroll)
	private:
		float m_DeltaX, m_DeltaY;
	};

	class MouseButtonEvent : public Event
	{
	public:
		MouseButtonEvent(int button) : m_Button(button) {}
		virtual int getButton() const { return m_Button; }
		EVENT_CREATE_CLASS_CATEGORY(EventCategory::Input | EventCategory::Mouse | EventCategory::MouseButton)
	private:
		int m_Button;
	};

	class MouseButtonDownEvent : public MouseButtonEvent
	{
	public:
		EVENT_CREATE_CLASS_TYPE(EventType::MouseDown)
	};

	class MouseButtonUpEvent : public MouseButtonEvent
	{
	public:
		EVENT_CREATE_CLASS_TYPE(EventType::MouseUp)
	};
}
