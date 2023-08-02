#include "GraphicsContext.h"

#include "Platform/OpenGL/OpenGLGraphicsContext.h"

namespace Magic {
	Ref<GraphicsContext> GraphicsContext::Create() {
		return CreateRef<OpenGLGraphicsContext>();
	}
}