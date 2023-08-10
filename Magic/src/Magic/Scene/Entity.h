#pragma once

#include <entt.hpp>
#include "Scene.h"
#include "Components.h"

namespace Magic {
	class Entity
	{
	public:
		Entity();
		Entity(entt::entity entityHandle, Scene* scene);
		~Entity();

		template<typename T, typename ...Args>
		T& AddComponent(Args &&... args)
		{
			return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}

		template<typename T, typename ...Args>
		T& AddOrReplaceComponent(Args&&...args)
		{
			return m_Scene->m_Registry.emplace_or_replace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		bool RemoveComponent()
		{
			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}

		template<typename T>
		T& GetComponent()
		{
			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

		template<typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}
	private:
		entt::entity m_EntityHandle;
		Scene* m_Scene;
	};
}
