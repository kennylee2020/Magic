#include "Renderer.h"
#include "Renderer2D.h"
#include "RenderPipeline.h"

namespace Magic {
	void Renderer::Init() {
		Renderer2D::Init();
		RenderPipeline::Init();
	}
}