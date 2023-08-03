#include "RendererAPI.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Magic {
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;
	Ref<RendererAPI> RendererAPI::CreateRendererAPI() {
		if (s_API == RendererAPI::API::OpenGL) {
			return CreateRef<OpenGLRendererAPI>();
		}
		MAG_CORE_CRITICAL("Unhandle RendererAIP {0}", (int)s_API);
		return nullptr;
	}
}