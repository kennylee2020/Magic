#include "magicpch.h"
#include "FrameBuffer.h"
#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLFrameBuffer.h"

namespace Magic {
	Ref<Framebuffer> Framebuffer::Create(const FramebufferDescriptor& desc)
	{
		RendererAPI::API api = RendererAPI::GetAPI();
		switch (api)
		{
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLFramebuffer>(desc);
		}
		return nullptr;
	}
}