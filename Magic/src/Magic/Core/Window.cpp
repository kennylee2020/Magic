#include "Window.h"
#include "Platform/Windows/WindowsWindow.h"

namespace Magic {
	std::shared_ptr<Window> Window::create(const Window::WindowDesc& windowDesc)
	{
		return std::make_shared<WindowsWindow>(windowDesc);
	}
}
