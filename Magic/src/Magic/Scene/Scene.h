#pragma once

#include <entt.hpp>
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
		Entity CreateEntity();
		Entity FindEntity(uint32_t entityID);
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
	private:
		friend class Entity;
		friend class RenderPipeline;
		friend class SceneSerializer;
		friend class ScriptEngine;
	};
}
