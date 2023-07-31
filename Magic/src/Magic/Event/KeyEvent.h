#pragma once
#include "Event.h"

namespace Magic {
	class KeyEvent : public Event {
	public:
		virtual int GetKeycode() const { return m_Keycode;}
		EVENT_CREATE_CLASS_CATEGORY(EventCategory::Input | EventCategory::Key)
	protected:
		KeyEvent(int keycode) : m_Keycode(keycode){}
	protected:
		int m_Keycode;
	};

	class KeyDownEvent : public KeyEvent {
	public:
		KeyDownEvent(int keycode,int repeat) : KeyEvent(keycode), m_Repeat(repeat){}
		bool IsRepeat(){ return m_Repeat; }

		EVENT_CREATE_CLASS_TYPE(EventType::KeyDown)
	private:
		bool m_Repeat;
	};

	class KeyUpEvent : public KeyEvent {
	public:
		KeyUpEvent(int keycode) : KeyEvent(keycode) {}

		EVENT_CREATE_CLASS_TYPE(EventType::KeyUp)
	};

	class KeyTypedEvent : public KeyEvent {
	public:
		KeyTypedEvent(int keycode) : KeyEvent(keycode) {}

		EVENT_CREATE_CLASS_TYPE(EventType::KeyTyped)
	};
}

