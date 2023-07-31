#include "magicpch.h"
#include "Shader.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Magic {
	std::shared_ptr<Shader> Shader::Create(std::string filePath) {
		return std::make_shared<OpenGLShader>(filePath);
	}
}