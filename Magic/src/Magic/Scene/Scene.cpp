#include "magicpch.h"
#include "Scene.h"
#include "Entity.h"
#include "Components.h"
#include "Magic/Pipeline/Renderer2D.h"

namespace Magic {
	Entity Scene::CreateEntity()
	{
		Entity e{ m_Registry.create(), this };
		return e;
	}
	
	void Scene::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispath<WindowResizeEvent>(BIND_EVENT_CALLBACK(Scene::OnWindowResize));
	}

	bool Scene::OnWindowResize(WindowResizeEvent& e) {
		float aspect = (float)e.GetWidth() / (float)e.GetHeight();
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view) {
			CameraComponent& cameraComponent = view.get<CameraComponent>(entity);
			cameraComponent.SetAspect(aspect);
		}
		return true;
	}
}
