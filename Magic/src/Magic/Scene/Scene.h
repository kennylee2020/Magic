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
		void OnEvent(Event& e);
	private:
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		entt::registry m_Registry;
	private:
		friend class Entity;
		friend class RenderPipeline;
		friend class SceneSerializer;
	};
}
