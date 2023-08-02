#include "Window.h"
#include "Platform/Windows/WindowsWindow.h"

namespace Magic {
	Ref<Window> Window::Create(const Window::WindowDesc& windowDesc)
	{
		return CreateRef<WindowsWindow>(windowDesc);
	}
}
