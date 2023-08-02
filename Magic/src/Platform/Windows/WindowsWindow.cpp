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
			data.windowEvent(KeyDownEvent(key, 0));
		}else if (action == GLFW_RELEASE) {
			WindowsWindow::WindowData& data = *(WindowsWindow::WindowData*)glfwGetWindowUserPointer(window);
			data.windowEvent(KeyUpEvent(key));
		}else if (action == GLFW_REPEAT) {
			WindowsWindow::WindowData& data = *(WindowsWindow::WindowData*)glfwGetWindowUserPointer(window);
			data.windowEvent(KeyDownEvent(key, 1));
		}
	}

	static void char_callback(GLFWwindow* window, unsigned int keycode)
	{	
		WindowsWindow::WindowData& data = *(WindowsWindow::WindowData*)glfwGetWindowUserPointer(window);
		data.windowEvent(KeyTypedEvent(keycode));
	}

	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		WindowsWindow::WindowData& data = *(WindowsWindow::WindowData*)glfwGetWindowUserPointer(window);
		data.windowEvent(MouseScrollEvent((float)xoffset, (float)yoffset));
	}

	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		WindowsWindow::WindowData& data = *(WindowsWindow::WindowData*)glfwGetWindowUserPointer(window);
		if (action == GLFW_PRESS) {
			data.windowEvent(MouseButtonDownEvent(button));
		}else if(action == GLFW_RELEASE) {
			data.windowEvent(MouseButtonUpEvent(button));
		}
	}

	static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
	{
		WindowsWindow::WindowData& data = *(WindowsWindow::WindowData*)glfwGetWindowUserPointer(window);
		data.windowEvent(MouseMoveEvent((float)xpos, (float)ypos));
	}

	static void window_close_callback(GLFWwindow* window)
	{
		WindowsWindow::WindowData& data = *(WindowsWindow::WindowData*)glfwGetWindowUserPointer(window);
		data.windowEvent(WindowCloseEvent());
	}

	static void window_size_callback(GLFWwindow* window, int width, int height)
	{
		WindowsWindow::WindowData& data = *(WindowsWindow::WindowData*)glfwGetWindowUserPointer(window);
		data.windowEvent(WindowResizeEvent(width, height));
	}

	static void window_focus_callback(GLFWwindow* window, int focused)
	{
		WindowsWindow::WindowData& data = *(WindowsWindow::WindowData*)glfwGetWindowUserPointer(window);
		if(focused){
			data.windowEvent(WindowFocusEvent());
		}else{
			data.windowEvent(WindowLostFocus());
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
		glfwSwapBuffers(m_Window);
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
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

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