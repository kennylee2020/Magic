#include "magicpch.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Magic/Event/Event.h"
#include "Magic/Core/Application.h"
#include "WindowsWindow.h"

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

namespace Magic {
	static void error_callback(int error, const char* description)
	{
		MAG_ERROR(description);
	}

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

	static void window_close_callback(GLFWwindow* window)
	{
		Application* app = (Application*)glfwGetWindowUserPointer(window);
		WindowCloseEvent event;
		app->onEvent(event);
	}

	static void window_size_callback(GLFWwindow* window, int width, int height)
	{
		Application* app = (Application*)glfwGetWindowUserPointer(window);
		WindowResizeEvent event(width, height);
		app->onEvent(event);
	}

	static void window_focus_callback(GLFWwindow* window, int focused)
	{
		Application* app = (Application*)glfwGetWindowUserPointer(window);
		if(focused){
			app->onEvent(WindowFocusEvent());
		}else{
			app->onEvent(WindowLostFocus());
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
	
	void WindowsWindow::onUpdate()
	{
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

	void WindowsWindow::setWindowEventCallback(const WindowEventFunc& callback)
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
		glfwSetWindowUserPointer(window, this);
		glfwSetKeyCallback(window, key_callback);
		glfwSetWindowCloseCallback(window, window_close_callback);
		glfwSetWindowSizeCallback(window, window_size_callback);
		glfwSetWindowFocusCallback(window, window_focus_callback);
	}

	void WindowsWindow::shutdow()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void* WindowsWindow::getNativeWindow()
	{
		return m_Window;
	}
}