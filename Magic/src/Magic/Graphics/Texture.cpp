#include "magicpch.h"
#include "Texture.h"

#include "Platform/OpenGL/OpenGLTexture.h"

namespace Magic {
	Ref<Texture2D> Texture2D::Create(std::string filePath) {
		return CreateRef<OpenGLTexture2D>(filePath);
	}
	
	Ref<Texture2D> Texture2D::Create(int width, int height, uint8_t* data) {
		return CreateRef<OpenGLTexture2D>(width, height, data);
	}
}