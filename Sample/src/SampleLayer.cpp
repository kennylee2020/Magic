#include "SampleLayer.h"
#include <imgui.h>
#include <glad/glad.h>

namespace Sample {
	SampleLayer::SampleLayer() : Layer("SampleLayer"){
		static const struct
		{
			float x, y;
			float r, g, b;
			float u, v;
		}vertices[3] =
		{
			{ -0.6f, -0.4f, 1.f, 0.f, 0.f, 0.f, 0.f },
			{  0.6f, -0.4f, 0.f, 1.f, 0.f, 1.f, 0.f },
			{   0.f,  0.6f, 0.f, 0.f, 1.f, 0.5f,1.f }
		};

		unsigned int indices[3] = { 0, 1, 2 };

		Magic::BufferLayout layout{
			{"vPos", Magic::ShaderDataType::Float2, 0},
			{"vCol", Magic::ShaderDataType::Float3, 0},
			{"vUV",  Magic::ShaderDataType::Float2, 0},
		};
		m_Buffer = Magic::Buffer::Create(layout);
		m_Buffer->SetBufferData(sizeof(vertices), vertices);
		m_Buffer->Bind();

		m_IndexBuffer = Magic::IndexBuffer::Create();
		m_IndexBuffer->SetBufferData(3, indices);
		m_IndexBuffer->Bind();

		m_PureColorShader = Magic::Shader::Create("assets/shader/pure_color.glsl");
		m_PureColorShader->Bind();
		m_PureColorShader->SetInt("u_Texture", 0);

		m_Texture = Magic::Texture2D::Create("assets/image/test_img.jpg");
		m_Texture->Bind(0);
	}

	void SampleLayer::OnUpdate()
	{
		m_PureColorShader->Bind();
		glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
	}	 
		 
	void SampleLayer::OnImGui()
	{	
		float floatValue = 0;
		ImGui::Begin("Magic");
		ImGui::DragFloat("Test Float", &floatValue);
		ImGui::End();
	}	 
		 
	void SampleLayer::OnEvent(Magic::Event& e)
	{	 
	}
}


