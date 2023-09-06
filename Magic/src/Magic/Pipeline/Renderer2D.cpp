#include "Renderer2D.h"
#include "Magic/Core/Math.h"

namespace Magic {
	Ref<Mesh> Renderer2D::Quad = nullptr;
	Renderer2D::RenderContext Renderer2D::s_Context;
	
	void Renderer2D::Init() {
		float vertices[] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		};
		uint32_t indices[] = { 0, 1, 2, 2, 3, 0 };

		Quad = Mesh::Create();
		Quad->AddBuffer({
			{"vPos", Magic::ShaderDataType::Float3, 0},
			{"vUV",  Magic::ShaderDataType::Float2, 0},
			{"vCol", Magic::ShaderDataType::Float4, 0},
			}, vertices, sizeof(vertices));
		Quad->SetIndexBuffer(indices, sizeof(indices) / sizeof(uint32_t));
	}

	void Renderer2D::BeginScene(const glm::mat4x4& vpMatrix)
	{
		s_Context.vpMatrix = vpMatrix;
	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::DrawMesh(const Ref<Mesh>& mesh, const Ref<Material>& material, const glm::mat4x4& localToWorld)
	{
		const glm::mat4x4& mvp = s_Context.vpMatrix * localToWorld;
		mesh->Bind();
		material->Bind();
		material->SetMatrix4x4("u_MVP", mvp);
		RendererCommand::DrawIndexed(mesh->GetIndexBuffer());
	}

	void Renderer2D::DrawFullScreenQuad(const Ref<Material>& material)
	{
		Ref<Mesh> mesh = Renderer2D::Quad;
		mesh->Bind();
		material->Bind();
		material->SetMatrix4x4("u_MVP", glm::scale(glm::mat4(1), glm::vec3(2.0f, 2.0f, 1.0f)));
		RendererCommand::DrawIndexed(mesh->GetIndexBuffer());
	}
}