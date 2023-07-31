#include "magicpch.h"
#include "Texture.h"

#include "Platform/OpenGL/OpenGLTexture.h"

namespace Magic {
	std::shared_ptr<Texture2D> Texture2D::Create(std::string filePath) {
		return std::make_shared<OpenGLTexture2D>(filePath);
	}
	
	std::shared_ptr<Texture2D> Texture2D::Create(int width, int height, uint8_t* data) {
		return std::make_shared<OpenGLTexture2D>(width, height, data);
	}
}