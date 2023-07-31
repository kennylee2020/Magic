#pragma once
#include <string>
#include "Magic/Graphics/Shader.h"

namespace Magic {
	class OpenGLShader : public Shader{
	public:
		OpenGLShader(std::string filePath);
		~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;
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