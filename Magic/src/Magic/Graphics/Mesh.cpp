#include "Mesh.h"
#include "RendererAPI.h"
#include "Platform/OpenGL/OpenGLMesh.h"

namespace Magic {
	Ref<Mesh> Mesh::Create() {
		RendererAPI::API api = RendererAPI::GetAPI();
		switch (api)
		{
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLMesh>();
		}
		return nullptr;
	}
}
