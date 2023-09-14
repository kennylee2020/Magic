#pragma once
#include "Magic/Graphics/Graphics.h"

namespace Magic {
	class Renderer2D
	{
	private:
		struct RenderContext{
			glm::mat4x4 vpMatrix;
		};
	public:
		static void Init();
		static void BeginScene(const glm::mat4x4& vpMatrix);
		static void EndScene();
		static void DrawMesh(const Ref<Mesh>& mesh, const Ref<Material>& material, const glm::mat4x4& localToWorld);
		static void DrawFullScreenQuad(const Ref<Material>& material);
		static void DrawString(const std::string& text, const Ref<Font>& font, const Ref<Material>& material, const glm::vec3& position);
	public:
		static Ref<Mesh> Quad;
	private:
		static RenderContext s_Context;
	};
}
