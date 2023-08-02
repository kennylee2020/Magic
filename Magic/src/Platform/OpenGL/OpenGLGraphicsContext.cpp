#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Magic/Core/Application.h"
#include "OpenGLGraphicsContext.h"

namespace Magic {
	void OpenGLGraphicsContext::Init(){
		Application* app = Application::GetApplication();
		std::shared_ptr<Window> window =  app->GetWindow();

		GLFWwindow* nativeWindow = (GLFWwindow*)window->GetNativeWindow();
		glfwMakeContextCurrent(nativeWindow);
		gladLoadGL();
		glfwSwapInterval(1);

		int width, height;
		glfwGetFramebufferSize(nativeWindow, &width, &height);
		
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);
	}
}