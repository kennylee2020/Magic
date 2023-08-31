#pragma once
#include "Magic/Scene/Components.h"

#include <entt.hpp>;
#include <glm/glm.hpp>;

namespace Magic {
	#define EntityID uint64_t

	struct ApplicationCallbacks
	{
		void(*Application_OnRuntimeStart)();
		void(*Application_OnRuntimeUpdate)();
		void(*Application_OnRuntimeStop)();
	};

	class ScriptGlue
	{
	public:
		struct InitPayload {
			//Application
			void (*Application_RegisterCallbacks)(ApplicationCallbacks applicationCallbacks);
			//Debug
			void (*Debug_Log)(const char* msg);
			void (*Debug_Warn)(const char* msg);
			void (*Debug_Error)(const char* msg);
			void (*Debug_Critical)(const char* msg);
			//Entity
			EntityID (*Entity_Create)();
			EntityID (*Entity_FindEntity)(const char* name);
			bool (*Entity_HasComponent)(EntityID entityID);
			//NameComponent
			void (*NameComponent_Create)(EntityID entityID);
			void (*NameComponent_SetName)(EntityID entityID, const char* name);
			const char* (*NameComponent_GetName)(EntityID entityID);
			//ScriptComponent
			void (*ScriptComponent_Create)(EntityID entityID, ScriptComponent::LifeCycleCallbacks lifeCycleCallbacks);
			//TransformComponent
			void (*TransformComponent_Create)(EntityID entityID);
			void (*TransformComponent_SetPosition)(EntityID entityID, glm::vec3 position);
			glm::vec3 (*TransformComponent_GetPosition)(EntityID entityID);
			void (*TransformComponent_SetEulerAngles)(EntityID entityID, glm::vec3 eulerAngles);
			glm::vec3(*TransformComponent_GetEulerAngles)(EntityID entityID);
			void (*TransformComponent_SetScale)(EntityID entityID, glm::vec3 scale);
			glm::vec3(*TransformComponent_GetScale)(EntityID entityID);
		};
	public:
		static void Register(InitPayload& payload);
	};
}