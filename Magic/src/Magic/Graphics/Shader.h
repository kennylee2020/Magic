#pragma once
#include <memory>
#include <string>
#include <glm/glm.hpp>

namespace Magic {
	class Shader
	{
	public:
		enum class ShaderType{
			None = 0,Vertex,Fragment,
		};
	public:
		Shader() = default;
		~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void SetInt(std::string name, int value) const = 0;
		virtual void SetFloat(std::string name, float value) const = 0;
		virtual void SetFloat2(std::string name, const glm::vec2& value) const = 0;
		virtual void SetFloat3(std::string name, const glm::vec3& value) const = 0;
		virtual void SetFloat4(std::string name, const glm::vec4& value) const = 0;
		virtual void SetMatrix3x3(std::string name, const glm::mat3x3& value) const = 0;
		virtual void SetMatrix4x4(std::string name, const glm::mat4x4& value) const = 0;
	public:
		static Ref<Shader> Create(std::string filePath);
	};
}
