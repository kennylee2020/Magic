#pragma once
#include "magicpch.h"
#include "Window.h"
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
	private:
		std::shared_ptr<Window> m_Window;
	private:
		friend int ::main(int argc, char** argv);
	};

	Application* CreateApplication();
}
