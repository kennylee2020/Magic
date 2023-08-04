#pragma once
#include "Camera.h"
#include "Magic/Graphics/Graphics.h";

namespace Magic {
	class Renderer2D
	{
	private:
		struct RenderContext{
			glm::mat4x4 vpMatrix;
		};
	public:
		static void Init();
		static void BeginScene(const Ref<Camera>& camera);
		static void EndScene();
		static void DrawMesh(const Ref<Mesh>& mesh, const Ref<Material>& material, const glm::mat4x4& localToWorld);
	public:
		static Ref<Mesh> Quad;
	private:
		static RenderContext s_Context;
	};
}
