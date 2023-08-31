#pragma once

#include <entt.hpp>
#include "Magic/Core/UUID.h"
#include "Magic/Event/Event.h"
#include "Magic/Event/WindowEvent.h"

namespace Magic {
	class Entity;
	class RenderPipeline;
	
	class Scene
	{
	public:
		Scene() = default;
		~Scene() = default;
		Entity CreateEntity(const std::string& name = std::string());
		Entity CreateEntity(UUID uuid, const std::string& name = std::string());
		Entity FindEntity(UUID entityID);
		Entity FindEntity(const std::string& name);
	public:
		void OnEvent(Event& e);
		void OnRuntimeStart();
		void OnRuntimeUpdate();
		void OnRuntimeStop();
	private:
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		entt::registry m_Registry;
		std::unordered_map<UUID, entt::entity> m_EntityMap;
	private:
		friend class Entity;
		friend class RenderPipeline;
		friend class SceneSerializer;
		friend class ScriptEngine;
	};
}
