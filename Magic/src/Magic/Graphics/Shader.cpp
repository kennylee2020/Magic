#include "magicpch.h"
#include "Shader.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Magic {
	Ref<Shader> Shader::Create(std::string filePath) {
		return CreateRef<OpenGLShader>(filePath);
	}
}