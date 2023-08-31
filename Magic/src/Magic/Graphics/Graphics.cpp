#include "Graphics.h"
#include "Magic/Pipeline/Renderer.h"
#include "Magic/Pipeline/Renderer2D.h"

namespace Magic {
	void Graphics::Init() {
		Mesh::Init();
		Renderer::Init();
		RendererCommand::Init();
	}

	void Graphics::Shutdown() {
		
	}

	void Graphics::OnWindowResize(int width, int height)
	{
		RendererCommand::SetViewPort(0, 0, width, height);
	}
}