#include "magicpch.h"
#include "Texture.h"
#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLTexture.h"

namespace Magic {
	Ref<Texture2D> Texture2D::Create(std::string filePath) {
		RendererAPI::API api = RendererAPI::GetAPI();
		switch (api)
		{
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLTexture2D>(filePath);
		}
		return nullptr;
	}
	
	Ref<Texture2D> Texture2D::Create(int width, int height, uint8_t* data) {
		RendererAPI::API api = RendererAPI::GetAPI();
		switch (api)
		{
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLTexture2D>(width, height, data);
		}
		return nullptr;
	}

	Ref<RenderTexture> RenderTexture::Create(Ref<Framebuffer> framebuffer) {
		RendererAPI::API api = RendererAPI::GetAPI();
		switch (api)
		{
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLRenderTexture>(framebuffer);
		}
		return nullptr;
	}
}