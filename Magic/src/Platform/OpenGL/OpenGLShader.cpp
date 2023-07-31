#include "magicpch.h"
#include "OpenGLShader.h"

#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Magic {
	static Shader::ShaderType StringToShaderType(std::string shaderTypeString) {
		if (shaderTypeString == "vertex") return Shader::ShaderType::Vertex;
		if (shaderTypeString == "fragment") return Shader::ShaderType::Fragment;
		MAG_CORE_ERROR("Unknow Shader Type");
		return Shader::ShaderType::None;
	}

	static int ShaderTypeToGLShaderType(Shader::ShaderType shaderType) {
		if (shaderType == Shader::ShaderType::Vertex) return GL_VERTEX_SHADER;
		if (shaderType == Shader::ShaderType::Fragment) return GL_FRAGMENT_SHADER;
		MAG_CORE_ERROR("Unknow Shader Type");
		return 0;
	}

	OpenGLShader::OpenGLShader(std::string filePath) {
		std::string shaderText = loadShaderFile(filePath);
		std::vector<ShaderDescriptor> shaderDescriptors = parseShaderText(shaderText);
		m_RenderId = createProgram(shaderDescriptors);
	}

	OpenGLShader::~OpenGLShader() {
		glDeleteProgram(m_RenderId);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RenderId);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetInt(std::string name, int value) const
	{
		GLint location = glGetUniformLocation(m_RenderId, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::SetFloat(std::string name, float value) const
	{
		GLint location = glGetUniformLocation(m_RenderId, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::SetFloat2(std::string name, const glm::vec2& value) const
	{
		GLint location = glGetUniformLocation(m_RenderId, name.c_str());
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::SetFloat3(std::string name, const glm::vec3& value) const
	{
		GLint location = glGetUniformLocation(m_RenderId, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::SetFloat4(std::string name, const glm::vec4& value) const
	{
		GLint location = glGetUniformLocation(m_RenderId, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::SetMatrix3x3(std::string name, const glm::mat3x3& value) const
	{
		GLint location = glGetUniformLocation(m_RenderId, name.c_str());
		glUniformMatrix3fv(location, 1, false, glm::value_ptr(value));
	}

	void OpenGLShader::SetMatrix4x4(std::string name, const glm::mat4x4& value) const
	{
		GLint location = glGetUniformLocation(m_RenderId, name.c_str());
		glUniformMatrix4fv(location, 1, false, glm::value_ptr(value));
	}

	std::string OpenGLShader::loadShaderFile(const std::string& filePath) const{
		std::string result;
		std::ifstream in(filePath, std::ios_base::in | std::ios_base::binary);
		if (!in.is_open()) {
			MAG_CORE_ERROR("Open Shader file failed!");
			return result;
		}

		in.seekg(0, std::ios::end);
		size_t size = in.tellg();
		if (size < 0) {
			MAG_CORE_ERROR("Read Shader file failed!");
			return result;
		}

		result.resize(size);
		in.seekg(0, std::ios::beg);
		in.read(&result[0], size);
		return result;
	}

	std::vector<OpenGLShader::ShaderDescriptor> OpenGLShader::parseShaderText(const std::string& shaderText) const{
		static const std::string programToken = "#program";
		static const size_t tokenSize = programToken.size();
		
		std::vector<OpenGLShader::ShaderDescriptor> shaderDescriptors;
		size_t tokenStart = shaderText.find(programToken);
		while (tokenStart != std::string::npos)
		{
			size_t eol = shaderText.find_first_of("\r\n", tokenStart);
			ASSERT(eol != std::string::npos, "Shader syntax error!");
			
			size_t nextLineStart = shaderText.find_first_not_of("\r\n", eol);
			ASSERT(nextLineStart != std::string::npos, "Shader syntax error!");

			size_t typeStart = tokenStart + tokenSize + 1;
			std::string typeText = shaderText.substr(typeStart, eol - typeStart);
			ShaderType shaderType = StringToShaderType(typeText);

			tokenStart = shaderText.find(programToken, nextLineStart);
			std::string text = tokenStart == std::string::npos ? shaderText.substr(nextLineStart) : shaderText.substr(nextLineStart, tokenStart - nextLineStart);
			shaderDescriptors.push_back({ shaderType, text });
		}
		return shaderDescriptors;
	}

	uint32_t OpenGLShader::createProgram(const std::vector<OpenGLShader::ShaderDescriptor>& shaderDescriptors) const
	{
		std::vector<GLint> shaderIds;
		for (OpenGLShader::ShaderDescriptor shaderDescriptor : shaderDescriptors) {
			const int glShaderType = ShaderTypeToGLShaderType(shaderDescriptor.type);
			const GLint shader = glCreateShader(glShaderType);
			const char* shaderText = shaderDescriptor.shaderText.c_str();
			glShaderSource(shader, 1, &shaderText, NULL);
			glCompileShader(shader);
			shaderIds.push_back(shader);
		}

		uint32_t program = glCreateProgram();
		for (GLint shader : shaderIds) {
			glAttachShader(program, shader);
		}
		glLinkProgram(program);

		GLint isLinked;
		glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE) {
			GLint errorLength;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &errorLength);

			std::vector<GLchar> errorLog(errorLength);
			glGetProgramInfoLog(program, errorLength, &errorLength, errorLog.data());
			MAG_CORE_ERROR("Program Link failed! {0}", errorLog.data());

			for (GLint shader : shaderIds) {
				glDeleteShader(shader);
			}
			glDeleteProgram(program);
		}else {
			for (GLint shader : shaderIds) {
				glDetachShader(program, shader);
				glDeleteShader(shader);
			}
		}
		return program;
	}
}