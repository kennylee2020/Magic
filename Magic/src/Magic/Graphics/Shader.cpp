#include "magicpch.h"
#include "Shader.h"
#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Magic {
	Ref<Shader> Shader::Create(std::string filePath) {
		RendererAPI::API api = RendererAPI::GetAPI();
		switch (api)
		{
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLShader>(filePath);
		}
		return nullptr;
	}
}