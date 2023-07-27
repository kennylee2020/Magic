#pragma once
#include "Event.h"

namespace Magic {
	class KeyEvent : public Event {
	public:
		KeyEvent(int keycode) : m_Keycode(keycode){}
		virtual int getKeycode() const { return m_Keycode;}
		EVENT_CREATE_CLASS_CATEGORY(EventCategory::Input | EventCategory::Key)
	private:
		int m_Keycode;
	};

	class KeyDownEvent : public Event {
	public:
		EVENT_CREATE_CLASS_TYPE(EventType::KeyDown)
	};

	class KeyUpEvent : public Event {
	public:
		EVENT_CREATE_CLASS_TYPE(EventType::KeyUp)
	};
}

