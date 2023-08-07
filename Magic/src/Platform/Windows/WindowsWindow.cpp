#include "magicpch.h"
#include <GLFW/glfw3.h>

#include "Magic/Core/Application.h"
#include "WindowsWindow.h"

namespace Magic {
	static void error_callback(int error, const char* description)
	{
		MAG_CORE_ERROR("{0}::{1}",error, description);
	}

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		if (action == GLFW_PRESS) {
			WindowsWindow::WindowData& data = *(WindowsWindow::WindowData*)glfwGetWindowUserPointer(window);
			KeyDownEvent e(key, 0);
			data.windowEvent(e);
		}else if (action == GLFW_RELEASE) {
			WindowsWindow::WindowData& data = *(WindowsWindow::WindowData*)glfwGetWindowUserPointer(window);
			KeyUpEvent e(key);
			data.windowEvent(e);
		}else if (action == GLFW_REPEAT) {
			WindowsWindow::WindowData& data = *(WindowsWindow::WindowData*)glfwGetWindowUserPointer(window);
			KeyDownEvent e(key, 1);
			data.windowEvent(e);
		}
	}

	static void char_callback(GLFWwindow* window, unsigned int keycode)
	{	
		WindowsWindow::WindowData& data = *(WindowsWindow::WindowData*)glfwGetWindowUserPointer(window);
		KeyTypedEvent e(keycode);
		data.windowEvent(e);
	}

	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		WindowsWindow::WindowData& data = *(WindowsWindow::WindowData*)glfwGetWindowUserPointer(window);
		MouseScrollEvent e((float)xoffset, (float)yoffset);
		data.windowEvent(e);
	}

	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		WindowsWindow::WindowData& data = *(WindowsWindow::WindowData*)glfwGetWindowUserPointer(window);
		if (action == GLFW_PRESS) {
			MouseButtonDownEvent e(button);
			data.windowEvent(e);
		}else if(action == GLFW_RELEASE) {
			MouseButtonUpEvent e(button);
			data.windowEvent(e);
		}
	}

	static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
	{
		WindowsWindow::WindowData& data = *(WindowsWindow::WindowData*)glfwGetWindowUserPointer(window);
		MouseMoveEvent e((float)xpos, (float)ypos);
		data.windowEvent(e);
	}

	static void window_close_callback(GLFWwindow* window)
	{
		WindowsWindow::WindowData& data = *(WindowsWindow::WindowData*)glfwGetWindowUserPointer(window);
		WindowCloseEvent e;
		data.windowEvent(e);
	}

	static void window_size_callback(GLFWwindow* window, int width, int height)
	{
		WindowsWindow::WindowData& data = *(WindowsWindow::WindowData*)glfwGetWindowUserPointer(window);
		WindowResizeEvent e(width, height);
		data.windowEvent(e);
	}

	static void window_focus_callback(GLFWwindow* window, int focused)
	{
		WindowsWindow::WindowData& data = *(WindowsWindow::WindowData*)glfwGetWindowUserPointer(window);
		if(focused){
			WindowFocusEvent e;
			data.windowEvent(e);
		}else{
			WindowLostFocus e;
			data.windowEvent(e);
		}
	}

	WindowsWindow::WindowsWindow(const WindowDesc& windowDesc) {
		m_Data.title = windowDesc.title;
		m_Data.width = windowDesc.width;
		m_Data.height = windowDesc.height;

		init(m_Data);
	}

	WindowsWindow::~WindowsWindow()
	{
		shutdow();
	}
	
	void WindowsWindow::OnUpdate()
	{
		m_GraphicsContext->SwapBuffers();
		glfwPollEvents();
	}

	void WindowsWindow::SetWindowEventCallback(const WindowEventFunc& callback)
	{
		m_Data.windowEvent = callback;
	}

	void WindowsWindow::init(const WindowData& data)
	{
		GLFWwindow* window;
		glfwSetErrorCallback(error_callback);

		if (!glfwInit()) {
			exit(EXIT_FAILURE);
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

		window = glfwCreateWindow(data.width, data.height, data.title.c_str(), NULL, NULL);
		if (!window)
		{
			exit(EXIT_FAILURE);
		}

		m_Window = window;
		glfwSetWindowUserPointer(window, &m_Data);
		glfwSetKeyCallback(window, key_callback);
		glfwSetCharCallback(window, char_callback);
		glfwSetScrollCallback(window, scroll_callback);
		glfwSetMouseButtonCallback(window, mouse_button_callback);
		glfwSetCursorPosCallback(window, cursor_pos_callback);
		glfwSetWindowCloseCallback(window, window_close_callback);
		glfwSetWindowSizeCallback(window, window_size_callback);
		glfwSetWindowFocusCallback(window, window_focus_callback);

		m_GraphicsContext = GraphicsContext::Create(this);
		m_GraphicsContext->Init();
	}

	void WindowsWindow::shutdow()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void* WindowsWindow::GetNativeWindow()
	{
		return m_Window;
	}
}