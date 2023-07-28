#pragma once
#include "magicpch.h"
#include "Window.h"
#include "Magic/Event/KeyEvent.h"
#include "Magic/Event/MouseEvent.h"
#include "Magic/Event/WindowEvent.h"

int main(int argc, char** argv);

namespace Magic {
	class Application
	{
	public:
		Application();
		~Application() = default;
		bool onEvent(Event& event);
	private:
		void run();
		bool onWindowCloseEvent(WindowCloseEvent& event);
		bool onWindowResizeEvent(WindowResizeEvent& event);
		bool onWindowFocusEvent(WindowFocusEvent& event);
		bool onWindowLostFocusEvent(WindowLostFocus& event);
		bool onMouseButtonDownEvent(MouseButtonDownEvent& event);
		bool onMouseButtonUpEvent(MouseButtonUpEvent& event);
		bool onMouseMoveEvent(MouseMoveEvent& event);
		bool onMouseScrollEvent(MouseScrollEvent& event);
		bool onKeyDownEvent(KeyDownEvent& event);
		bool onKeyUpEvent(KeyUpEvent& event);
		bool onKeyTypedEvent(KeyTypedEvent& event);
	private:
		std::shared_ptr<Window> m_Window;
	private:
		friend int ::main(int argc, char** argv);
	};

	Application* CreateApplication();
}
