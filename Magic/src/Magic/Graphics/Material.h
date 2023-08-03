#pragma once
#include "magicpch.h"
#include "Shader.h"
#include "Texture.h"

namespace Magic {
	class Material {
	public:
		Material(const Ref<Shader>& shader);
		void Bind() const;
		void Unbind() const;
		void SetInt(std::string name, int value) const;
		void SetFloat(std::string name, float value) const;
		void SetFloat2(std::string name, const glm::vec2& value) const;
		void SetFloat3(std::string name, const glm::vec3& value) const;
		void SetFloat4(std::string name, const glm::vec4& value) const;
		void SetMatrix3x3(std::string name, const glm::mat3x3& value) const;
		void SetMatrix4x4(std::string name, const glm::mat4x4& value) const;
		void SetTexture(std::string name, const Ref<Texture>& texture);
	public:
		static Ref<Material> Create(const Ref<Shader>& shader);
	private:
		Ref<Shader> m_Shader;
		std::vector<Ref<Texture>> m_Textures;
	};
}