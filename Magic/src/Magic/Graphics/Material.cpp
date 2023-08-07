#include "Material.h"

namespace Magic {
	Ref<Material> Material::Create(const Ref<Shader>& shader) {
		return CreateRef<Material>(shader);
	}

	Material::Material(const Ref<Shader>& shader) : m_Shader(shader)
	{
	}

	void Material::Bind() const
	{
		int slotIndex = 0;
		for (const Ref<Texture>& texture : m_Textures) {
			texture->Bind(slotIndex++);
		}
		m_Shader->Bind();
	}
	
	void Material::Unbind() const
	{
		m_Shader->Unbind();
	}

	void Material::SetInt(std::string name, int value) const
	{
		m_Shader->SetInt(name, value);
	}

	void Material::SetFloat(std::string name, float value) const
	{
		m_Shader->SetFloat(name, value);
	}

	void Material::SetFloat2(std::string name, const glm::vec2& value) const
	{
		m_Shader->SetFloat2(name, value);
	}

	void Material::SetFloat3(std::string name, const glm::vec3& value) const
	{
		m_Shader->SetFloat3(name, value);
	}

	void Material::SetFloat4(std::string name, const glm::vec4& value) const
	{
		m_Shader->SetFloat4(name, value);
	}

	void Material::SetMatrix3x3(std::string name, const glm::mat3x3& value) const
	{
		m_Shader->SetMatrix3x3(name, value);
	}

	void Material::SetMatrix4x4(std::string name, const glm::mat4x4& value) const
	{
		m_Shader->SetMatrix4x4(name, value);
	}

	void Material::SetTexture(std::string name, const Ref<Texture>& texture)
	{
		int slotIndex = (int)m_Textures.size();
		m_Shader->SetInt(name, slotIndex);
		m_Textures.push_back(texture);
	}
}