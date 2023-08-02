#include "GraphicsContext.h"

#include "Platform/OpenGL/OpenGLGraphicsContext.h"

namespace Magic {
	std::shared_ptr<GraphicsContext> GraphicsContext::Create() {
		return std::make_shared<OpenGLGraphicsContext>();
	}
}