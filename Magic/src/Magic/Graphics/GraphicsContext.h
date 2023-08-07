#pragma once

#include <memory>
#include "Magic/Core/Window.h"

namespace Magic {
	class GraphicsContext {
	public:
		virtual ~GraphicsContext() = default;
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	public:
		static Ref<GraphicsContext> Create(Window* window);
	};
}