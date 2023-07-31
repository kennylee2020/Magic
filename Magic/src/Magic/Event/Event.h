#pragma once
#include "Magic/Core/Base.h"

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
		bool Handled = false;
		virtual EventType GetType() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string GetName() const = 0;
		virtual std::string ToString() const { return GetName(); }
		virtual bool IsInCategory(EventCategory category){ return GetCategoryFlags() & category; }
		virtual ~Event() = default;
	};

	class EventDispatcher {
	public:
		EventDispatcher(Event& event) : m_Event(event){}

		template<typename T, typename F>
		bool Dispath(const F& func) {
			if (m_Event.GetType() == T::getStaticType()) {
				m_Event.Handled |= func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	//std::ostream& operator<<(std::ostream& os, const Magic::Event& e)
	//{
	//	return os << e.toString();
	//};

#define EVENT_CREATE_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override {return category;}
#define EVENT_CREATE_CLASS_TYPE(type) static EventType getStaticType() {return type;}\
									  virtual EventType GetType() const override {return getStaticType();}\
									  virtual std::string GetName() const override {return #type;}
};


