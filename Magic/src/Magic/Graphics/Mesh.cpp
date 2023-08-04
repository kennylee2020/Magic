#include "Mesh.h"
#include "RendererAPI.h"
#include "Platform/OpenGL/OpenGLMesh.h"

namespace Magic {
	static float s_cube_vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // A 0
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // B 1
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // C 2
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // D 3
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // E 4
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // F 5
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // G 6
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // H 7
										 						
		-0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // D 8
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // A 9
		-0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // E 10
		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // H 11
		 0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // B 12
		 0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // C 13
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // G 14
		 0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // F 15
																
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // A 16
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // B 17
		 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // F 18
		-0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // E 19
		 0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // C 20
		-0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // D 21
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // H 22
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // G 23
	};
	static uint32_t s_cube_elements[] = {
		// front and back
		0, 3, 2,
		2, 1, 0,
		4, 5, 6,
		6, 7 ,4,
		// left and right
		11, 8, 9,
		9, 10, 11,
		12, 13, 14,
		14, 15, 12,
		// bottom and top
		16, 17, 18,
		18, 19, 16,
		20, 21, 22,
		22, 23, 20
	};
	
	Ref<Mesh> Mesh::Cube = nullptr;
	void Mesh::Init() {
		Cube = Mesh::Create();
		Cube->AddBuffer({
			{"vPos", Magic::ShaderDataType::Float3, 0},
			{"vUV",  Magic::ShaderDataType::Float2, 0},
			{"vCol", Magic::ShaderDataType::Float4, 0},
		}, s_cube_vertices, sizeof(s_cube_vertices));
		Cube->SetIndexBuffer(s_cube_elements, sizeof(s_cube_elements) / sizeof(uint32_t));
	}

	Ref<Mesh> Mesh::Create() {
		RendererAPI::API api = RendererAPI::GetAPI();
		switch (api)
		{
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLMesh>();
		}
		return nullptr;
	}
}
