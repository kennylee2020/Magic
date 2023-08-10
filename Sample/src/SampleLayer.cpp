#include "SampleLayer.h"
#include <imgui.h>

namespace Sample {
	SampleLayer::SampleLayer() : Layer("SampleLayer"){
		m_Material = Magic::Material::Create(Magic::Shader::Create("assets/shader/pure_color.glsl"));
		m_Material->SetTexture("u_Texture", Magic::Texture2D::Create("assets/image/test_img.png"));
		m_Material->Bind();

		m_Scene = Magic::CreateRef<Magic::Scene>();

		Magic::Entity& cameraEntity = m_Scene->CreateEntity();
		cameraEntity.AddComponent<Magic::TransformComponent>(glm::vec3(0.0f, 0.0f, 0.0f));
		cameraEntity.AddComponent<Magic::CameraComponent>(2.0f, 4.0f / 3.0f, true);
		m_CameraEntity = cameraEntity;

		Magic::Entity& cameraEntity2 = m_Scene->CreateEntity();
		cameraEntity2.AddComponent<Magic::TransformComponent>(glm::vec3(2.0f, 0.0f, 0.0f));
		cameraEntity2.AddComponent<Magic::CameraComponent>(5.0f, 4.0f / 3.0f, true);

		Magic::Entity& entity = m_Scene->CreateEntity();
		entity.AddComponent<Magic::TransformComponent>(glm::vec3(0.0f, 0.0f, -1.0f));
		entity.AddComponent<Magic::MeshComponent>(Magic::Renderer2D::Quad);
		entity.AddComponent<Magic::MaterialComponent>(m_Material);
	}

	void SampleLayer::OnUpdate()
	{
		Magic::RenderPipeline::Render(m_Scene);
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
		dispatcher.Dispath<Magic::KeyDownEvent>(BIND_EVENT_CALLBACK(SampleLayer::OnKeyDownEvent));

		m_Scene->OnEvent(e);
	}

	bool SampleLayer::OnKeyDownEvent(Magic::KeyDownEvent& e)
	{
		const float Speed = 1.0f * 0.03f;
		if (e.GetKeycode() == Magic::Key::A) {
			Magic::TransformComponent& transformComponent = m_CameraEntity.GetComponent<Magic::TransformComponent>();
			glm::vec3 positon = transformComponent.GetPosition();
			positon.x -= Speed;
			transformComponent.SetPosition(positon);
		}
		else if (e.GetKeycode() == Magic::Key::D) {
			Magic::TransformComponent& transformComponent = m_CameraEntity.GetComponent<Magic::TransformComponent>();
			glm::vec3 positon = transformComponent.GetPosition();
			positon.x += Speed;
			transformComponent.SetPosition(positon);
		}
		else if (e.GetKeycode() == Magic::Key::W) {
			Magic::TransformComponent& transformComponent = m_CameraEntity.GetComponent<Magic::TransformComponent>();
			glm::vec3 positon = transformComponent.GetPosition();
			positon.y += Speed;
			transformComponent.SetPosition(positon);
		}
		else if (e.GetKeycode() == Magic::Key::S) {
			Magic::TransformComponent& transformComponent = m_CameraEntity.GetComponent<Magic::TransformComponent>();
			glm::vec3 positon = transformComponent.GetPosition();
			positon.y -= Speed;
			transformComponent.SetPosition(positon);
		}
		return false;
	}
}


