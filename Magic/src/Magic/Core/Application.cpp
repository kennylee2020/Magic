#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "magicpch.h"
#include "Magic/Event/Event.h"
#include "Magic/Core/Application.h"

#include "Magic/Graphics/Buffer.h"

#include <stdio.h>
#include <stdlib.h>

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

#include <stb_image.h>

namespace Magic {
	Application::Application()
	{
		MAG_CORE_INFO("Magic start!");
		m_IsRunning = true;
		m_Window = Window::Create({ "Magic", 640, 480 });
		m_Window->SetWindowEventCallback(BIND_EVENT_CALLBACK(Application::OnEvent));

		GLFWwindow* window = (GLFWwindow*)m_Window->GetNativeWindow();
		glfwMakeContextCurrent(window);
		gladLoadGL();
		glfwSwapInterval(1);

		glfwMakeContextCurrent(window);
		gladLoadGL();
		glfwSwapInterval(1);
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	bool Application::OnEvent(Event& e) {
		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			if (e.Handled) break;
			(*it)->OnEvent(e);
		}

		EventDispatcher dispatcher(e);
		dispatcher.Dispath<WindowCloseEvent>(BIND_EVENT_CALLBACK(Application::onWindowCloseEvent));
		dispatcher.Dispath<WindowResizeEvent>(BIND_EVENT_CALLBACK(Application::onWindowResizeEvent));
		dispatcher.Dispath<WindowFocusEvent>(BIND_EVENT_CALLBACK(Application::onWindowFocusEvent));
		dispatcher.Dispath<WindowLostFocus>(BIND_EVENT_CALLBACK(Application::onWindowLostFocusEvent));

		dispatcher.Dispath<MouseButtonDownEvent>(BIND_EVENT_CALLBACK(Application::onMouseButtonDownEvent));
		dispatcher.Dispath<MouseButtonUpEvent>(BIND_EVENT_CALLBACK(Application::onMouseButtonUpEvent));
		dispatcher.Dispath<MouseScrollEvent>(BIND_EVENT_CALLBACK(Application::onMouseScrollEvent));
		dispatcher.Dispath<MouseMoveEvent>(BIND_EVENT_CALLBACK(Application::onMouseMoveEvent));

		dispatcher.Dispath<KeyDownEvent>(BIND_EVENT_CALLBACK(Application::onKeyDownEvent));
		dispatcher.Dispath<KeyUpEvent>(BIND_EVENT_CALLBACK(Application::onKeyUpEvent));
		dispatcher.Dispath<KeyTypedEvent>(BIND_EVENT_CALLBACK(Application::onKeyTypedEvent));
		return true;
	}

	bool Application::onWindowFocusEvent(WindowFocusEvent& e) {
		MAG_INFO("onWindowFocusEvent");
		return true;
	}

	bool Application::onWindowCloseEvent(WindowCloseEvent& e) {
		MAG_INFO("onWindowCloseEvent");
		m_IsRunning = false;
		return true;
	}

	bool Application::onWindowResizeEvent(WindowResizeEvent& e) {
		MAG_INFO("onWindowResizeEvent");
		return true;
	}

	bool Application::onWindowLostFocusEvent(WindowLostFocus& e) {
		MAG_INFO("onWindowLostFocusEvent");
		return true;
	}

	bool Application::onMouseButtonDownEvent(MouseButtonDownEvent& e)
	{
		MAG_INFO("onMouseButtonDownEvent");
		return true;
	}

	bool Application::onMouseButtonUpEvent(MouseButtonUpEvent& e)
	{
		MAG_INFO("onMouseButtonUpEvent");
		return true;
	}

	bool Application::onMouseMoveEvent(MouseMoveEvent& e)
	{
		//MAG_INFO("onMouseMoveEvent {0} {1}", event.getX(), event.getY());
		return true;
	}

	bool Application::onMouseScrollEvent(MouseScrollEvent& e)
	{
		//MAG_INFO("onMouseScrollEvent {0} {1}", event.getDeltaX(), event.getDeltaY());
		return true;
	}

	bool Application::onKeyDownEvent(KeyDownEvent& e)
	{
		MAG_INFO("onKeyDownEvent");
		return true;
	}

	bool Application::onKeyUpEvent(KeyUpEvent& e)
	{
		MAG_INFO("onKeyUpEvent");
		return true;
	}

	bool Application::onKeyTypedEvent(KeyTypedEvent& e)
	{
		MAG_INFO("onKeyTypedEvent {0}", e.GetKeycode());
		return true;
	}

	void Application::run()
	{
		GLFWwindow* window = (GLFWwindow*)m_Window->GetNativeWindow();

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init();
	
		while (m_IsRunning)
		{
			float ratio;
			int width, height;

			glfwGetFramebufferSize(window, &width, &height);
			ratio = width / (float)height;

			glViewport(0, 0, width, height);
			glClear(GL_COLOR_BUFFER_BIT);
			
			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			////ImGui::ShowDemoWindow();
			for (Layer* layer : m_LayerStack) {
				layer->OnImGui();
			}
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			m_Window->OnUpdate();
		}

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	
		exit(EXIT_SUCCESS);
	}
}