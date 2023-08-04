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
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLGraphicsContext::SwapBuffers() {
		GLFWwindow* nativeWindow = (GLFWwindow*)m_Window->GetNativeWindow();
		glfwSwapBuffers(nativeWindow);
	}
}