#include "GraphicsContext.h"
#include "RendererAPI.h"
#include "Magic/Core/Window.h"
#include "Platform/OpenGL/OpenGLGraphicsContext.h"

namespace Magic {
	Ref<GraphicsContext> GraphicsContext::Create(Window* window) {
		RendererAPI::API api = RendererAPI::GetAPI();
		switch (api)
		{
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLGraphicsContext>(window);
		}
		return nullptr;
	}
}