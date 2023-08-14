#include "SceneSerializer.h"
#include "Entity.h"
#include "Magic/Core/Application.h"

#include <fstream>

namespace YAML {
	template<>
	struct convert<glm::vec2> {
		static Node encode(const glm::vec2& rhs) {
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			return node;
		}

		static bool decode(const Node& node, glm::vec2& rhs) {
			if (!node.IsSequence() || node.size() != 2) {
				return false;
			}

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::vec3> {
		static Node encode(const glm::vec3& rhs) {
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			return node;
		}

		static bool decode(const Node& node, glm::vec3& rhs) {
			if (!node.IsSequence() || node.size() != 3) {
				return false;
			}

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::vec4> {
		static Node encode(const glm::vec4& rhs) {
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			return node;
		}

		static bool decode(const Node& node, glm::vec4& rhs) {
			if (!node.IsSequence() || node.size() != 4) {
				return false;
			}

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
			return true;
		}
	};
}

namespace Magic {
	YAML::Emitter& operator << (YAML::Emitter& out, const glm::vec2& v) {
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator << (YAML::Emitter& out, const glm::vec3& v) {
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator << (YAML::Emitter& out, const glm::vec4& v) {
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
		return out;
	}

	SceneSerializer::SceneSerializer(const Ref<Scene>& scene) : m_Scene(scene)
	{
	}

	bool SceneSerializer::Serialize(const std::string& filepath)
	{
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << "Unnamed";
		
		out << YAML::Key << "Entities";
		out << YAML::Value;
		{
			out << YAML::BeginSeq;
			m_Scene->m_Registry.each([&](auto entityId) {
				Entity entity{ entityId, m_Scene.get() };
				SerializeEntity(out, entity);
				});
			out << YAML::EndSeq;
		}

		out << YAML::EndMap;

		std::ofstream fout(filepath);
		fout << out.c_str();

		return out.good();
	}

	bool SceneSerializer::Deserialize(const std::string& filepath)
	{
		YAML::Node config = YAML::LoadFile(filepath);

		YAML::Node entities = config["Entities"];
		for (YAML::Node entityNode : entities) {
			DeserializeEntity(entityNode);
		}
		return false;
	}
	
	void SceneSerializer::SerializeEntity(YAML::Emitter& out, Entity entity)
	{
		out << YAML::BeginMap;

		out << YAML::Key << "ID" << YAML::Value << entity;
		//NameComponent
		if (entity.HasComponent<NameComponent>()) {
			const NameComponent& nameComponent = entity.GetComponent<NameComponent>();
			out << YAML::Key << "NameComponent" << YAML::Value << nameComponent.Name;
		}
		//TransformComponent
		if (entity.HasComponent<TransformComponent>()) {
			const TransformComponent& transformComponent = entity.GetComponent<TransformComponent>();
			out << YAML::Key << "TransformComponent";
			out << YAML::Value;
			{
				out << YAML::BeginMap;
				out << YAML::Key << "Position" << YAML::Value << transformComponent.GetPosition();
				out << YAML::Key << "EulerAngles" << YAML::Value << transformComponent.GetEulerAngles();
				out << YAML::Key << "Scale" << YAML::Value << transformComponent.GetScale();
				out << YAML::EndMap;
			}
		}
		//CameraComponent
		if (entity.HasComponent<CameraComponent>()) {
			const CameraComponent& cameraComponent = entity.GetComponent<CameraComponent>();
			out << YAML::Key << "CameraComponent";
			out << YAML::Value;
			{
				out << YAML::BeginMap;
				out << YAML::Key << "SizeOrFov" << YAML::Value << cameraComponent.GetSizeOrFov();
				out << YAML::Key << "Orthographic" << YAML::Value << cameraComponent.IsOrthographic();
				out << YAML::Key << "Near" << YAML::Value << cameraComponent.GetNearPlane();
				out << YAML::Key << "Far" << YAML::Value << cameraComponent.GetFarPlane();
				out << YAML::EndMap;
			}
		}

		out << YAML::EndMap;
	}

	void SceneSerializer::DeserializeEntity(YAML::Node& entityNode)
	{
		Entity entity = m_Scene->CreateEntity();

		YAML::Node nameComponent = entityNode["NameComponent"];
		if (nameComponent) {
			const std::string& name = nameComponent.as<std::string>();
			entity.AddComponent<NameComponent>(name);
		}

		YAML::Node transformComponent = entityNode["TransformComponent"];
		if (transformComponent) {
			glm::vec3 position = transformComponent["Position"].as<glm::vec3>();
			glm::vec3 eulerAngles = transformComponent["EulerAngles"].as<glm::vec3>();
			glm::vec3 scale = transformComponent["Scale"].as<glm::vec3>();
			entity.AddComponent<TransformComponent>(position, eulerAngles, scale);
		}

		YAML::Node cameraComponent = entityNode["CameraComponent"];
		if (cameraComponent) {
			Ref<Window> window = Application::GetApplication()->GetWindow();
			float aspect = (float)window->GetWidth() / (float)window->GetHeight();
			float sizeOrFov = cameraComponent["SizeOrFov"].as<float>();
			bool orthographic = cameraComponent["Orthographic"].as<bool>();
			float nearPlane = cameraComponent["Near"].as<float>();
			float farPlane = cameraComponent["Far"].as<float>();
			entity.AddComponent<CameraComponent>(sizeOrFov, aspect, orthographic, nearPlane, farPlane);
		}
	}
}