#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "magicpch.h"
#include "Application.h"
#include <stdio.h>
#include <stdlib.h>

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

namespace Magic {
	Application::Application()
	{
		Log::Init();
		MAG_INFO_CORE("Magic start!");
	}

	Application::~Application()
	{
	}

	static void error_callback(int error, const char* description)
	{
		fprintf(stderr, "Error: %s\n", description);
	}

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

	void Application::Run()
	{
		GLFWwindow* window;
		glfwSetErrorCallback(error_callback);

		if (!glfwInit()) {
			exit(EXIT_FAILURE);
		}
		
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

		window = glfwCreateWindow(640, 480, "Magic", NULL, NULL);
		if (!window)
		{
			glfwTerminate();
			exit(EXIT_FAILURE);
		}

		glfwSetKeyCallback(window, key_callback);

		glfwMakeContextCurrent(window);
		gladLoadGL();
		glfwSwapInterval(1);

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

		static const char* vertex_shader_text =
			"#version 110\n"
			"uniform mat4 MVP;\n"
			"attribute vec3 vCol;\n"
			"attribute vec2 vPos;\n"
			"varying vec3 color;\n"
			"void main()\n"
			"{\n"
			"    gl_Position = vec4(vPos, 0.0, 1.0);\n"
			"    color = vCol;\n"
			"}\n";

		static const char* fragment_shader_text =
			"#version 110\n"
			"varying vec3 color;\n"
			"void main()\n"
			"{\n"
			"    gl_FragColor = vec4(color, 1.0);\n"
			"}\n";


		GLuint vertex_buffer, vertex_shader, fragment_shader, program;
		GLint mvp_location, vpos_location, vcol_location;
		glGenBuffers(1, &vertex_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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

		glEnableVertexAttribArray(vpos_location);
		glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
			sizeof(vertices[0]), (void*)0);
		glEnableVertexAttribArray(vcol_location);
		glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
			sizeof(vertices[0]), (void*)(sizeof(float) * 2));

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		ImGui_ImplGlfw_InitForOpenGL(window,true);
		ImGui_ImplOpenGL3_Init();

		while (!glfwWindowShouldClose(window))
		{
			float ratio;
			int width, height;

			glfwGetFramebufferSize(window, &width, &height);
			ratio = width / (float)height;

			glViewport(0, 0, width, height);
			glClear(GL_COLOR_BUFFER_BIT);

			glUseProgram(program);
			//glDrawArrays(GL_TRIANGLES, 0, 3);

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

			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		glfwDestroyWindow(window);

		glfwTerminate();
		exit(EXIT_SUCCESS);
	}
}