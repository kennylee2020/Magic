#include "magicpch.h"
#include "ScriptGlue.h"
#include "ScriptEngine.h"
#include "Magic/Scene/Entity.h"
#include "Magic/Scene/Components.h"

namespace Magic {
	namespace ApplicationCLR {
		static void RegisterCallbaks(ApplicationCallbacks callbacks) {
			ScriptEngine::RegisterApplicationCallbacks(callbacks);
		}
	}

	namespace DebugCLR {
		static void Log(const char* msg) {
			MAG_INFO(msg);
		}

		static void Warn(const char* msg) {
			MAG_WARN(msg);
		}

		static void Error(const char* msg) {
			MAG_ERROR(msg);
		}

		static void Critical(const char* msg) {
			MAG_CRITICAL(msg);
		}
	}

	namespace EntityCLR {
		static EntityID Create() {
			Entity e = ScriptEngine::GetSceneContext()->CreateEntity();
			return e.GetID();
		}

		static EntityID FindEntity(const char* name) {
			Entity e = ScriptEngine::GetSceneContext()->FindEntity(name);
			return e ? e.GetID() : 0;
		}

		static bool HasComponent(EntityID entityID) {
			return false;
		}
	}

	namespace NameComponentCLR {
		static void Create(EntityID entityID) {
			Entity entity = ScriptEngine::GetSceneContext()->FindEntity(entityID);
			if (!entity.HasComponent<NameComponent>()) {
				entity.AddComponent<NameComponent>();
			}
		}

		static void SetName(EntityID entityID, const char* name) {
			Entity entity = ScriptEngine::GetSceneContext()->FindEntity(entityID);
			NameComponent& nameComponent = entity.GetComponent<NameComponent>();
			nameComponent.Name = name;
		}

		static const char* GetName(EntityID entityID) {
			Entity entity = ScriptEngine::GetSceneContext()->FindEntity(entityID);
			NameComponent& nameComponent = entity.GetComponent<NameComponent>();
			return nameComponent.Name.c_str();
		}
	}

	namespace ScriptComponentCLR {
		static void Create(EntityID entityID, ScriptComponent::LifeCycleCallbacks lifeCycleMethod) {
			Entity entity = ScriptEngine::GetSceneContext()->FindEntity(entityID);
			if (!entity.HasComponent<ScriptComponent>()){
				ScriptComponent& script = entity.AddComponent<ScriptComponent>(lifeCycleMethod);
			}
		}
	}

	namespace TransformComponentCLR {
		static void Create(EntityID entityID) {
			Entity entity = ScriptEngine::GetSceneContext()->FindEntity(entityID);
			if (!entity.HasComponent<TransformComponent>()) entity.AddComponent<TransformComponent>();
		}

		static void SetPosition(EntityID entityID, glm::vec3 position) {
			Entity entity = ScriptEngine::GetSceneContext()->FindEntity(entityID);
			TransformComponent& transformComponent = entity.GetComponent<TransformComponent>();
			transformComponent.SetPosition(position);
		}

		static glm::vec3 GetPosition(EntityID entityID) {
			Entity entity = ScriptEngine::GetSceneContext()->FindEntity(entityID);
			TransformComponent& transformComponent = entity.GetComponent<TransformComponent>();
			return transformComponent.GetPosition();
		}

		static void SetEulerAngles(EntityID entityID, glm::vec3 eulerAngles) {
			Entity entity = ScriptEngine::GetSceneContext()->FindEntity(entityID);
			TransformComponent& transformComponent = entity.GetComponent<TransformComponent>();
			transformComponent.SetEulerAngles(eulerAngles);
		}

		static glm::vec3 GetEulerAngles(EntityID entityID) {
			Entity entity = ScriptEngine::GetSceneContext()->FindEntity(entityID);
			TransformComponent& transformComponent = entity.GetComponent<TransformComponent>();
			return transformComponent.GetEulerAngles();
		}

		static void SetScale(EntityID entityID, glm::vec3 scale) {
			Entity entity = ScriptEngine::GetSceneContext()->FindEntity(entityID);
			TransformComponent& transformComponent = entity.GetComponent<TransformComponent>();
			transformComponent.SetScale(scale);
		}

		static glm::vec3 GetScale(EntityID entityID) {
			Entity entity = ScriptEngine::GetSceneContext()->FindEntity(entityID);
			TransformComponent& transformComponent = entity.GetComponent<TransformComponent>();
			return transformComponent.GetScale();
		}
	}
}

namespace Magic {
	void ScriptGlue::Register(InitPayload& payload)
	{
		payload = {
			ApplicationCLR::RegisterCallbaks,
			DebugCLR::Log,
			DebugCLR::Warn,
			DebugCLR::Error,
			DebugCLR::Critical,
			EntityCLR::Create,
			EntityCLR::FindEntity,
			EntityCLR::HasComponent,
			NameComponentCLR::Create,
			NameComponentCLR::SetName,
			NameComponentCLR::GetName,
			ScriptComponentCLR::Create,
			TransformComponentCLR::Create,
			TransformComponentCLR::SetPosition,
			TransformComponentCLR::GetPosition,
			TransformComponentCLR::SetEulerAngles,
			TransformComponentCLR::GetEulerAngles,
			TransformComponentCLR::SetScale,
			TransformComponentCLR::GetScale,
		};
	}
}