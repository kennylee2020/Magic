#pragma once
#include "Magic/Scene/Components.h"

#include <entt.hpp>;
#include <glm/glm.hpp>;

namespace Magic {
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
			uint32_t (*Entity_Create)();
			uint32_t (*Entity_FindEntity)(const char* name);
			bool (*Entity_HasComponent)(uint32_t entityID);
			//NameComponent
			void (*NameComponent_Create)(uint32_t entityID);
			void (*NameComponent_SetName)(uint32_t entityID, const char* name);
			const char* (*NameComponent_GetName)(uint32_t entityID);
			//ScriptComponent
			void (*ScriptComponent_Create)(uint32_t entityID, ScriptComponent::LifeCycleCallbacks lifeCycleCallbacks);
			//TransformComponent
			void (*TransformComponent_Create)(uint32_t entityID);
			void (*TransformComponent_SetPosition)(uint32_t entityID, glm::vec3 position);
			glm::vec3 (*TransformComponent_GetPosition)(uint32_t entityID);
			void (*TransformComponent_SetEulerAngles)(uint32_t entityID, glm::vec3 eulerAngles);
			glm::vec3(*TransformComponent_GetEulerAngles)(uint32_t entityID);
			void (*TransformComponent_SetScale)(uint32_t entityID, glm::vec3 scale);
			glm::vec3(*TransformComponent_GetScale)(uint32_t entityID);
		};
	public:
		static void Register(InitPayload& payload);
	};
}