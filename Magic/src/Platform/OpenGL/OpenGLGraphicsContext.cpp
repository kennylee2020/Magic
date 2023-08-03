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

		int width, height;
		glfwGetFramebufferSize(nativeWindow, &width, &height);
		
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLGraphicsContext::SwapBuffers() {
		GLFWwindow* nativeWindow = (GLFWwindow*)m_Window->GetNativeWindow();
		glfwSwapBuffers(nativeWindow);
	}
}