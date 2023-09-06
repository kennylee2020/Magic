#include "magicpch.h"
#include "Shader.h"
#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLShader.h"

/// <summary>
/// SPIRV
/// 1、Use libshaderc compiling shader strings into SPIR-V.
/// https://github.com/google/shaderc/tree/main/libshaderc
/// 2、Use SPIR-V binary cross comiple to other platform.
/// https://github.com/KhronosGroup/SPIRV-Cross/tree/main
/// 3、Some leaning references
/// https://vulkan-tutorial.com/Drawing_a_triangle/Graphics_pipeline_basics/Shader_modules#page_Compiling-the-shaders
/// 
/// </summary>

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