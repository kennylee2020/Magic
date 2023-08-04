#include "SampleLayer.h"
#include <imgui.h>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

namespace Sample {
	SampleLayer::SampleLayer() : Layer("SampleLayer"){
		static const struct
		{
			float x, y, z;
			float r, g, b, a;
			float u, v;
		}vertices[3] =
		{
			{ -0.6f, -0.4f, 0.f, 0.f, 0.f, 0.f, 1.0f, 1.f, 0.f, },
			{  0.6f, -0.4f, 0.f, 0.f, 1.f, 0.f, 1.0f, 0.f, 1.f, },
			{   0.f,  0.6f, 0.f, 1.f, 0.5f,1.f, 1.0f, 0.f, 0.f, }
		};

		uint32_t indices[3] = { 0, 1, 2 };

		Magic::BufferLayout layout{
			{"vPos", Magic::ShaderDataType::Float3, 0},
			{"vUV",  Magic::ShaderDataType::Float2, 0},
			{"vCol", Magic::ShaderDataType::Float4, 0},
		};
		m_Mesh = Magic::Mesh::Create();
		m_Mesh->AddBuffer(layout, vertices, sizeof(vertices));
		m_Mesh->SetIndexBuffer(indices, sizeof(indices) /  sizeof(uint32_t));
		m_Mesh->Bind();

		m_Material = Magic::Material::Create(Magic::Shader::Create("assets/shader/pure_color.glsl"));
		m_Material->SetTexture("u_Texture", Magic::Texture2D::Create("assets/image/test_img.png"));
		m_Material->Bind();
	}

	void SampleLayer::OnUpdate()
	{
		Magic::RendererCommand::Clear();
		//Magic::Graphics::DrawMesh(m_Mesh, m_Material, glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.0f, 0.0f)));
		//Magic::Graphics::DrawMesh(m_Mesh, m_Material, glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, 0.0f, 0.0f)));
		Magic::Graphics::DrawMesh(m_Mesh, m_Material, glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, 0.5f, 0.0f)));
		static float angle = 0;
		Magic::Graphics::DrawMesh(Magic::Mesh::Cube, m_Material, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.5f))
			* glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f))
			* glm::scale(glm::mat4(1.0f), glm::vec3(0.5f)));
		angle += 1.0f;
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


