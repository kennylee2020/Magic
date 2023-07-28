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
		MAG_INFO_CORE("Magic start!");
		m_Window = Window::create({ "Magic", 640, 480 });
		m_Window->setWindowEventCallback(BIND_EVENT_CALLBACK(Application::onEvent));
	}

	bool Application::onEvent(Event& event) {
		EventDispatcher dispatcher(event);
		dispatcher.dispath<WindowCloseEvent>(BIND_EVENT_CALLBACK(Application::onWindowCloseEvent));
		dispatcher.dispath<WindowResizeEvent>(BIND_EVENT_CALLBACK(Application::onWindowResizeEvent));
		dispatcher.dispath<WindowFocusEvent>(BIND_EVENT_CALLBACK(Application::onWindowFocusEvent));
		dispatcher.dispath<WindowLostFocus>(BIND_EVENT_CALLBACK(Application::onWindowLostFocusEvent));

		dispatcher.dispath<MouseButtonDownEvent>(BIND_EVENT_CALLBACK(Application::onMouseButtonDownEvent));
		dispatcher.dispath<MouseButtonUpEvent>(BIND_EVENT_CALLBACK(Application::onMouseButtonUpEvent));
		dispatcher.dispath<MouseScrollEvent>(BIND_EVENT_CALLBACK(Application::onMouseScrollEvent));
		dispatcher.dispath<MouseMoveEvent>(BIND_EVENT_CALLBACK(Application::onMouseMoveEvent));

		dispatcher.dispath<KeyDownEvent>(BIND_EVENT_CALLBACK(Application::onKeyDownEvent));
		dispatcher.dispath<KeyUpEvent>(BIND_EVENT_CALLBACK(Application::onKeyUpEvent));
		dispatcher.dispath<KeyTypedEvent>(BIND_EVENT_CALLBACK(Application::onKeyTypedEvent));
		return true;
	}

	bool Application::onWindowFocusEvent(WindowFocusEvent& event) {
		MAG_INFO("onWindowFocusEvent");
		return true;
	}

	bool Application::onWindowCloseEvent(WindowCloseEvent& event) {
		MAG_INFO("onWindowCloseEvent");
		return true;
	}

	bool Application::onWindowResizeEvent(WindowResizeEvent& event) {
		MAG_INFO("onWindowResizeEvent");
		return true;
	}

	bool Application::onWindowLostFocusEvent(WindowLostFocus& event) {
		MAG_INFO("onWindowLostFocusEvent");
		return true;
	}

	bool Application::onMouseButtonDownEvent(MouseButtonDownEvent& event)
	{
		MAG_INFO("onMouseButtonDownEvent");
		return true;
	}

	bool Application::onMouseButtonUpEvent(MouseButtonUpEvent& event)
	{
		MAG_INFO("onMouseButtonUpEvent");
		return true;
	}

	bool Application::onMouseMoveEvent(MouseMoveEvent& event)
	{
		//MAG_INFO("onMouseMoveEvent {0} {1}", event.getX(), event.getY());
		return true;
	}

	bool Application::onMouseScrollEvent(MouseScrollEvent& event)
	{
		//MAG_INFO("onMouseScrollEvent {0} {1}", event.getDeltaX(), event.getDeltaY());
		return true;
	}

	bool Application::onKeyDownEvent(KeyDownEvent& event)
	{
		MAG_INFO("onKeyDownEvent");
		return true;
	}

	bool Application::onKeyUpEvent(KeyUpEvent& event)
	{
		MAG_INFO("onKeyUpEvent");
		return true;
	}

	bool Application::onKeyTypedEvent(KeyTypedEvent& event)
	{
		MAG_INFO("onKeyTypedEvent {0}", event.getKeycode());
		return true;
	}

	void Application::run()
	{
		static const struct
		{
			float x, y;
			float r, g, b;
		}vertices[3] =
		{
			{ -0.6f, -0.4f, 1.f, 0.f, 0.f },
			{  0.6f, -0.4f, 0.f, 1.f, 0.f },
			{   0.f,  0.6f, 0.f, 0.f, 1.f }
		};

		unsigned int indices[3] = {0, 1, 2};

		static const char* vertex_shader_text =
			"#version 330 core\n"
			"uniform mat4 MVP;\n"
			"layout(location = 0) in vec2 vPos;\n"
			"layout(location = 1) in vec3 vCol;\n"
			"varying vec3 color;\n"
			"void main()\n"
			"{\n"
			"    gl_Position = vec4(vPos, 0.0, 1.0);\n"
			"    color = vCol;\n"
			"}\n";

		static const char* fragment_shader_text =
			"#version 330 core\n"
			"varying vec3 color;\n"
			"void main()\n"
			"{\n"
			"    gl_FragColor = vec4(color, 1.0);\n"
			"}\n";

		GLFWwindow* window = (GLFWwindow*)m_Window->getNativeWindow();
		glfwMakeContextCurrent(window);
		gladLoadGL();
		glfwSwapInterval(1);

		GLuint vertex_shader, fragment_shader, program;
		GLint mvp_location, vpos_location, vcol_location;

		vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
		glCompileShader(vertex_shader);

		fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
		glCompileShader(fragment_shader);

		program = glCreateProgram();
		glAttachShader(program, vertex_shader);
		glAttachShader(program, fragment_shader);
		glLinkProgram(program);

		mvp_location = glGetUniformLocation(program, "MVP");
		vpos_location = glGetAttribLocation(program, "vPos");
		vcol_location = glGetAttribLocation(program, "vCol");

		BufferLayout layout{
			{"vPos", ShaderDataType::Float2, 0},
			{"vCol", ShaderDataType::Float3, 0},
		};
		std::shared_ptr<Buffer> buffer = Buffer::create(layout);
		buffer->setBufferData(sizeof(vertices), vertices);
		buffer->bind();

		std::shared_ptr<IndexBuffer> indexBuffer = IndexBuffer::create();
		indexBuffer->setBufferData(3, indices);
		indexBuffer->bind();

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init();

		glfwMakeContextCurrent(window);
		gladLoadGL();
		glfwSwapInterval(1);

		int width,height,channel;
		stbi_uc* data = stbi_load("assets/image/test_img.jpg",&width,&height,&channel,3);
		if(data){
			MAG_INFO_CORE("Load Successed!");
		}else {
			MAG_INFO_CORE("Load Failed!");
		}
		stbi_image_free(data);

		while (!glfwWindowShouldClose(window))
		{
			float ratio;
			int width, height;

			glfwGetFramebufferSize(window, &width, &height);
			ratio = width / (float)height;

			glViewport(0, 0, width, height);
			glClear(GL_COLOR_BUFFER_BIT);

			glUseProgram(program);
			glDrawElements(GL_TRIANGLES, indexBuffer->getCount(), GL_UNSIGNED_INT, nullptr);

			float Translate = 0;
			glm::vec2 Rotate(0, 0);
			glm::mat4 Projection = glm::perspective(glm::pi<float>() * 0.25f, 4.0f / 3.0f, 0.1f, 100.f);
			glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
			View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
			View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
			glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			ImGui::ShowDemoWindow();

			float floatValue = 0;
			ImGui::Begin("Magic");
			ImGui::DragFloat("Test Float", &floatValue);
			ImGui::End();

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			m_Window->onUpdate();
		}

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	
		exit(EXIT_SUCCESS);
	}
}