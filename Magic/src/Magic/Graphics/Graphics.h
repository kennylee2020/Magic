#pragma once
#include "Magic/Graphics/Buffer.h"
#include "Magic/Graphics/Shader.h"
#include "Magic/Graphics/Texture.h"
#include "Magic/Graphics/Mesh.h"
#include "Magic/Graphics/Material.h"
#include "Magic/Graphics/RendererCommand.h"

namespace Magic {
	class Graphics {
	public:
		static void Init();
		static void OnWindowResize(int width,int height);
	};
}
