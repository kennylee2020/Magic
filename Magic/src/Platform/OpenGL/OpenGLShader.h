#pragma once
#include <string>
#include <glm/glm.hpp>
#include "Magic/Graphics/Shader.h"

namespace Magic {
	class OpenGLShader : public Shader{
	public:
		OpenGLShader(std::string filePath);
		~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void SetInt(std::string name, int value) const override;
		virtual void SetFloat(std::string name, float value) const override;
		virtual void SetFloat2(std::string name, const glm::vec2& value) const override;
		virtual void SetFloat3(std::string name, const glm::vec3& value) const override;
		virtual void SetFloat4(std::string name, const glm::vec4& value) const override;
		virtual void SetMatrix3x3(std::string name, const glm::mat3x3& value) const override;
		virtual void SetMatrix4x4(std::string name, const glm::mat4x4& value) const override;
	private:
		struct ShaderDescriptor
		{
			Shader::ShaderType type;
			std::string shaderText;
		};
	private:
		uint32_t m_RenderId;
	private:
		std::string loadShaderFile(const std::string& filePath) const;
		std::vector<OpenGLShader::ShaderDescriptor> parseShaderText(const std::string& shaderText) const;
		uint32_t createProgram(const std::vector<OpenGLShader::ShaderDescriptor>& shaderParseDatas) const;
	};
}