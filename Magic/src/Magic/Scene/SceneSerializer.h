#pragma once
#include "Scene.h"
#include <yaml-cpp/yaml.h>

namespace Magic {
	class SceneSerializer {
	public:
		SceneSerializer(const Ref<Scene>& scene);
		~SceneSerializer() = default;
		bool Serialize(const std::string& filepath);
		bool Deserialize(const std::string& filepath);
	private:
		void SerializeEntity(YAML::Emitter& out, Entity entity);
		void DeserializeEntity(YAML::Node& entityNode);
	private:
		Ref<Scene> m_Scene;
	};
}