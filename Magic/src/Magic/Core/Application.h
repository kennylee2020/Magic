#pragma once
#include "Window.h"
#include "Magic/Core/Layer.h"
#include "Magic/Event/KeyEvent.h"
#include "Magic/Event/MouseEvent.h"
#include "Magic/Event/WindowEvent.h"

#include "Magic/Graphics/GraphicsContext.h"
#include "Magic/Graphics/Shader.h"
#include "Magic/Graphics/Texture.h"

int main(int argc, char** argv);

namespace Magic {
	class Application
	{
	public:
		struct ApplicationDesc{
			Window::WindowDesc windowDesc;
		};
	public:
		Application(const ApplicationDesc desc);
		virtual ~Application();
		void PushLayer(Layer* layer);
		bool OnEvent(Event& event);
		Ref<Window> GetWindow() const { return m_Window; }
	public:
		static inline Application* GetApplication() { return s_Instance; }
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
		bool m_IsRunning;
		Ref<Window> m_Window;
		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;
	private:
		friend int ::main(int argc, char** argv);
	};

	Application* CreateApplication();
}
