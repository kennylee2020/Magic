#include "Buffer.h"
#include "RendererAPI.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Magic {
	Ref<Buffer> Buffer::Create(const BufferLayout& layout) {
		RendererAPI::API api = RendererAPI::GetAPI();
		switch (api)
		{
		case RendererAPI::API::OpenGL: 
			return CreateRef<OpenGLBuffer>(layout);
		}
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create() {
		RendererAPI::API api = RendererAPI::GetAPI();
		switch (api)
		{
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLIndexBuffer>();
		}
		return nullptr;
	}

	Ref<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding)
	{
		RendererAPI::API api = RendererAPI::GetAPI();
		switch (api)
		{
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLUniformBuffer>(size, binding);
		}
		return nullptr;
	}
}