#include "RenderPipeline.h"
#include "Renderer2D.h"
#include "Magic/Scene/Entity.h"
#include "Magic/Scene/Components.h"

namespace Magic {

	void RenderPipeline::Init() 
	{
	}

	void RenderPipeline::Render(const Ref<Scene>& scene)
	{
		BeginRendering();
		RenderCameras(scene);
		EndRendering();
	}

	void RenderPipeline::BeginRendering()
	{
		RendererCommand::Clear();
	}

	void RenderPipeline::EndRendering()
	{
	}

	void RenderPipeline::RenderCameras(const Ref<Scene>& scene) {
		auto view = scene->m_Registry.view<TransformComponent, CameraComponent>();
		for (auto entity : view) {
			TransformComponent& transformComponent = view.get<TransformComponent>(entity);
			CameraComponent& cameraComponent = view.get<CameraComponent>(entity);
			RenderCamera(cameraComponent, transformComponent, scene);
		}
	}

	void RenderPipeline::RenderCamera(const CameraComponent& camera, const TransformComponent& transform, const Ref<Scene>& scene)
	{
		Renderer2D::BeginScene(camera.GetProjection() * transform.GetWorldToLocalMatrix());
		auto view = scene->m_Registry.view<TransformComponent, MeshComponent, MaterialComponent>();
		for (auto entity : view) {
			TransformComponent& transformComponent = view.get<TransformComponent>(entity);
			MeshComponent& meshComponent = view.get<MeshComponent>(entity);
			MaterialComponent& materialComponent = view.get<MaterialComponent>(entity);
			Renderer2D::DrawMesh(meshComponent.mesh, materialComponent.material, transformComponent.GetLocalToWorldMatrix());
		}
		Renderer2D::EndScene();
	}
}