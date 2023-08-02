#pragma once

#include "Magic/Graphics/GraphicsContext.h"

namespace Magic {
	class OpenGLGraphicsContext : public GraphicsContext {
	public:
		virtual void Init() override;
	};
}