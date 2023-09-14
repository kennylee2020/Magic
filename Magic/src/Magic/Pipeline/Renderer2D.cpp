#include "Renderer2D.h"
#include "Magic/Core/Math.h"
#include "Magic/Core/Application.h"

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

	//Just for test,actually this method can be replaced by DrawMesh!
	void Renderer2D::DrawString(const std::string& text, const Ref<Font>& font, const Ref<Material>& material, const glm::vec3& position)
	{
		Ref<Mesh> mesh = Mesh::Create();
		std::vector<float> vertices;
		std::vector<uint32_t> elements;
		Ref<Texture> texture = font->GetTexture(0);
		float w = 1.0f / texture->GetWidth();
		float h = 1.0f / texture->GetHeight();

		font->SetFontSize(18);
		float scale = font->GetScale() * font->GetFontSize();
		float lineHeight = font->GetLineHeight();
		
		int index = 0;
		glm::vec2 pos(0,0);
		for (int i = 0; i < text.length(); i++) {
			const char& c = text[i];
			Glyph glyph = font->GetGlyph(c);
			if(c == '\n'){
				pos.x = 0;
				pos.y -= lineHeight * scale;
				continue;
			}

			glm::vec2 advance = glm::vec2(glyph.advance.h * scale, glyph.advance.v * scale);

			glm::vec2 minTexCol = glm::vec2(glyph.imageBounds.l * w, glyph.imageBounds.b * h);
			glm::vec2 maxTexCol = glm::vec2(glyph.imageBounds.r * w, glyph.imageBounds.t * h);

			glm::vec2 minPos = glm::vec2(glyph.planeBounds.l * scale, glyph.planeBounds.b * scale);
			glm::vec2 maxPos = glm::vec2(glyph.planeBounds.r * scale, glyph.planeBounds.t * scale);
			
			//0
			vertices.push_back(pos.x + minPos.x);
			vertices.push_back(pos.y + minPos.y);
			vertices.push_back(0);

			vertices.push_back(minTexCol.x);
			vertices.push_back(minTexCol.y);

			vertices.push_back(1);
			vertices.push_back(1);
			vertices.push_back(1);
			vertices.push_back(1);

			//1
			vertices.push_back(pos.x + maxPos.x);
			vertices.push_back(pos.y + minPos.y);
			vertices.push_back(0);

			vertices.push_back(maxTexCol.x);
			vertices.push_back(minTexCol.y);

			vertices.push_back(1);
			vertices.push_back(1);
			vertices.push_back(1);
			vertices.push_back(1);

			//2
			vertices.push_back(pos.x + maxPos.x);
			vertices.push_back(pos.y + maxPos.y);
			vertices.push_back(0);

			vertices.push_back(maxTexCol.x);
			vertices.push_back(maxTexCol.y);

			vertices.push_back(1);
			vertices.push_back(1);
			vertices.push_back(1);
			vertices.push_back(1);

			//3
			vertices.push_back(pos.x + minPos.x);
			vertices.push_back(pos.y + maxPos.y);
			vertices.push_back(0);

			vertices.push_back(minTexCol.x);
			vertices.push_back(maxTexCol.y);

			vertices.push_back(1);
			vertices.push_back(1);
			vertices.push_back(1);
			vertices.push_back(1);

			pos += advance;

			//elements
			elements.push_back(index + 0);
			elements.push_back(index + 1);
			elements.push_back(index + 2);
			elements.push_back(index + 2);
			elements.push_back(index + 3);
			elements.push_back(index + 0);
			index += 4;
		}
		mesh->AddBuffer({
			{"vPos", Magic::ShaderDataType::Float3, 0},
			{"vUV",  Magic::ShaderDataType::Float2, 0},
			{"vCol", Magic::ShaderDataType::Float4, 0},
		}, vertices.data(), vertices.size() * sizeof(float));
		mesh->SetIndexBuffer(elements.data(), elements.size());
		mesh->Bind();

		Ref<Window> window = Application::GetApplication()->GetWindow();
		float halfWidth = window->GetWidth() * 0.5f;
		float halfHeight = window->GetHeight() * 0.5f;

		glm::mat4x4 projection = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, 0.01f, 100.0f) 
			* glm::translate(glm::mat4(1), glm::vec3(-halfWidth, -halfHeight, -50))
			* glm::translate(glm::mat4(1), position);
		material->Bind();
		material->SetFloat("u_PixelRange", 2);
		material->SetTexture("u_FontTexture", texture);
		material->SetMatrix4x4("u_MVP", projection);
		material->Bind();
		RendererCommand::DrawIndexed(mesh->GetIndexBuffer());
	}
}