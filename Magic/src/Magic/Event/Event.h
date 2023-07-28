#pragma once
#include "magicpch.h"

namespace Magic {
	class Event
	{
	public:
		enum class EventType
		{
			None = 0,
			WindowClose,WindowResize,WindowFocus,WindowLostFocus,
			MouseButtonDown,MouseButtonUp,MouseMove,MouseScroll,
			KeyDown,KeyUp,KeyTyped,
		};
		enum EventCategory 
		{
			None =			0,
			Window =		BIT(1),
			Input =			BIT(2),
			Mouse =			BIT(3),
			MouseButton =   BIT(4),
			Key =			BIT(5),
		};
	public:
		bool handled = false;
		virtual EventType getType() const = 0;
		virtual int getCategoryFlags() const = 0;
		virtual std::string getName() const = 0;
		virtual std::string toString() const { return getName(); }
		virtual bool isInCategory(EventCategory category){ return getCategoryFlags() & category; }
		virtual ~Event() = default;
	};

	class EventDispatcher {
	public:
		EventDispatcher(Event& event) : m_Event(event){}

		template<typename T, typename F>
		bool dispath(const F& func) {
			if (m_Event.getType() == T::getStaticType()) {
				m_Event.handled |= func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	//inline std::ostream& operator<<(std::ostream& os, const Event& e)
	//{
	//	return os << e.toString();
	//}

#define EVENT_CREATE_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override {return category;}
#define EVENT_CREATE_CLASS_TYPE(type) static EventType getStaticType() {return type;}\
									  virtual EventType getType() const override {return getStaticType();}\
									  virtual std::string getName() const override {return #type;}
}
