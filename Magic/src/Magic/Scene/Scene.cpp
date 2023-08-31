#include "magicpch.h"
#include "Scene.h"
#include "Entity.h"
#include "Components.h"
#include "Magic/Pipeline/Renderer2D.h"
#include "Magic/Scripting/ScriptEngine.h"

namespace Magic {
	Entity Scene::CreateEntity(const std::string& name)
	{
		return CreateEntity(UUID(), name);
	}

	Entity Scene::CreateEntity(UUID uuid, const std::string& name)
	{
		Entity e{ m_Registry.create(), this };
		e.AddComponent<IDComponent>(uuid);
		e.AddComponent<NameComponent>(name.empty() ? "Entity" : name);

		IDComponent idComponent = e.GetComponent<IDComponent>();

		m_EntityMap[uuid] = e;
		return e;
	}

	Entity Scene::FindEntity(const std::string& name)
	{
		auto view = m_Registry.view<NameComponent>();
		for (auto entity : view) {
			NameComponent& nameComponent = view.get<NameComponent>(entity);
			if (nameComponent.Name == name) {
				return { entity , this};
			}
		}
		return Entity();
	}

	Entity Scene::FindEntity(UUID uuid)
	{
		if (m_EntityMap.find(uuid) != m_EntityMap.end()) {
			return {m_EntityMap.at(uuid), this};
		}
		return {};
	}
	
	void Scene::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispath<WindowResizeEvent>(BIND_EVENT_CALLBACK(Scene::OnWindowResize));
	}

	void Scene::OnRuntimeStart()
	{
		ScriptEngine::OnRuntimeStart(this);
	}

	void Scene::OnRuntimeUpdate()
	{
		ScriptEngine::OnRuntimeUpdate();
	}

	void Scene::OnRuntimeStop()
	{
		ScriptEngine::OnRuntimeStop();
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
