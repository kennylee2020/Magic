#pragma once
#include <memory>
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
			WindowDesc(const std::string title = "Magic", int width = 640, int height = 360) : title(title), width(width), height(height) {}
		};
		typedef std::function<bool(Event& e)> WindowEventFunc;
	public:
		virtual ~Window() = default;
		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;
		virtual void OnUpdate() = 0;
		virtual void* GetNativeWindow() = 0;
		virtual void SetWindowEventCallback(const WindowEventFunc& callback) = 0;

		static Ref<Window> Create(const WindowDesc& windowDesc);
	};
}
