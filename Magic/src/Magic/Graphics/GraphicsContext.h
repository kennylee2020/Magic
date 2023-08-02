#pragma once

#include <memory>

namespace Magic {
	class GraphicsContext {
	public:
		virtual void Init() = 0;
	public:
		static Ref<GraphicsContext> Create();
	};
}