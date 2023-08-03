#pragma once

#include "Magic/Graphics/GraphicsContext.h"

namespace Magic {
	class OpenGLGraphicsContext : public GraphicsContext {
	public:
		OpenGLGraphicsContext(Window* window);
		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		Window* m_Window;
	};
}