#include "Entity.h"

namespace Magic {
	Entity::Entity():m_EntityHandle(entt::null),m_Scene(nullptr)
	{
	}

	Entity::Entity(entt::entity entityHandle, Scene* scene) : m_EntityHandle(entityHandle), m_Scene(scene)
	{
	}

	Entity::~Entity()
	{
	}
}