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

		inline UUID GetID() { return GetComponent<IDComponent>().ID; }
		inline const std::string& GetName() { return GetComponent<NameComponent>().Name; }

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
			return m_Scene->m_Registry.any_of<T>(m_EntityHandle);
		}
	public:
		operator entt::entity() const { return m_EntityHandle; }
		operator uint32_t() const { return (uint32_t)m_EntityHandle; }
		
		operator bool() const { return m_EntityHandle != entt::null; }

		bool operator==(const Entity& other) {
			return m_EntityHandle == other.m_EntityHandle && m_Scene == other.m_Scene;
		}

		bool operator!=(const Entity& other) {
			return !(*this == other);
		}
	private:
		entt::entity m_EntityHandle;
		Scene* m_Scene;
	};
}
