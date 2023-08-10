#pragma once
#include "magicpch.h"
#include "Magic/Scene/Components.h"
#include "Magic/Scene/Scene.h"

namespace Magic {
	class RenderPipeline
	{
	public:
		static void Render(const Ref<Scene>& scene);
	private:
		static void BeginRendering();
		static void EndRendering();
		static void RenderCamera(const CameraComponent& camera, const TransformComponent& transform, const Ref<Scene>& scene);
	};
}