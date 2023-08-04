#pragma once
#include "Mesh.h";
#include "Material.h"
#include "RendererCommand.h"

namespace Magic {
	class Graphics
	{
	public:
		inline static void Init() {
			Mesh::Init();
		}

		inline static void DrawMesh(const Ref<Mesh>& mesh, const Ref<Material>& material, const glm::mat4x4& localToWorld) {
			mesh->Bind();
			material->Bind();
			material->SetMatrix4x4("MVP", localToWorld);
			RendererCommand::DrawIndexed(mesh->GetIndexBuffer());
		}
	};
}
