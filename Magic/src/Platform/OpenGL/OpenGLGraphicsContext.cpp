#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Magic/Core/Application.h"
#include "OpenGLGraphicsContext.h"

namespace Magic {
	OpenGLGraphicsContext::OpenGLGraphicsContext(Window* window) : m_Window(window){
	}

	void OpenGLGraphicsContext::Init(){
		GLFWwindow* nativeWindow = (GLFWwindow*)m_Window->GetNativeWindow();
		glfwMakeContextCurrent(nativeWindow);
		gladLoadGL();
		glfwSwapInterval(1);
	}

	void OpenGLGraphicsContext::SwapBuffers() {
		GLFWwindow* nativeWindow = (GLFWwindow*)m_Window->GetNativeWindow();
		glfwSwapBuffers(nativeWindow);
	}
}