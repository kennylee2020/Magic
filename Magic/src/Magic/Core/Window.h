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
		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;
		virtual void OnUpdate() = 0;
		virtual void* GetNativeWindow() = 0;
		virtual void SetWindowEventCallback(const WindowEventFunc& callback) = 0;

		static std::shared_ptr<Window> Create(const WindowDesc& windowDesc);
	};
}
