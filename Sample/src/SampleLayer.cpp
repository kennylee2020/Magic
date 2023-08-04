#include "SampleLayer.h"
#include <imgui.h>

namespace Sample {
	SampleLayer::SampleLayer() : Layer("SampleLayer"){
		m_Camera = Magic::Camera::CreateOrthographic(1.0f, 4.0f/ 3.0f);
		m_Material = Magic::Material::Create(Magic::Shader::Create("assets/shader/pure_color.glsl"));
		m_Material->SetTexture("u_Texture", Magic::Texture2D::Create("assets/image/test_img.png"));
		m_Material->Bind();
	}

	void SampleLayer::OnUpdate()
	{
		Magic::RendererCommand::Clear();
		Magic::Renderer2D::BeginScene(m_Camera);
		Magic::Renderer2D::DrawMesh(Magic::Renderer2D::Quad, m_Material, glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, 0.0f, -1.0f)));
		Magic::Renderer2D::DrawMesh(Magic::Renderer2D::Quad, m_Material, glm::translate(glm::mat4(1.0f), glm::vec3( 0.0f, 0.0f, -1.0f)));
		Magic::Renderer2D::EndScene();
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
		Magic::EventDispatcher dispatcher(e);
		dispatcher.Dispath<Magic::WindowResizeEvent>(BIND_EVENT_CALLBACK(SampleLayer::OnWindowResize));
	}

	bool SampleLayer::OnWindowResize(Magic::WindowResizeEvent& e) {
		m_Camera->SetAspect((float)e.GetWidth() / (float)e.GetHeight());
		return true;
	}
}


