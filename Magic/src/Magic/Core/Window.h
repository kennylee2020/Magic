#pragma once
#include <string>
#include "Magic/Event/Event.h"

namespace Magic {
	class Window
	{
	public:
		struct WindowDesc
		{
			int width;
			int height;
			std::string title;
			WindowDesc(const std::string title,int width, int height) : title(title),width(width),height(height){}
		};
		typedef std::function<bool(Event& e)> WindowEventFunc;
	public:
		virtual int getWidth() const = 0;
		virtual int getHeight() const = 0;
		virtual void onUpdate() = 0;
		virtual void* getNativeWindow() = 0;
		virtual void setWindowEventCallback(const WindowEventFunc& callback) = 0;

		static std::shared_ptr<Window> Create(const WindowDesc& windowDesc);
	};
}
