#pragma once
#include "magicpch.h"
#include "Magic/Graphics/Mesh.h"

namespace Magic {
	class OpenGLMesh : public Mesh {
	public:
		OpenGLMesh();
		~OpenGLMesh();
		virtual void AddBuffer(const BufferLayout& layout, const void* data, uint32_t size) override;
		virtual void SetIndexBuffer(const uint32_t* data, uint32_t count) override;
		virtual Ref<IndexBuffer>& GetIndexBuffer() override;
		virtual void Clear() override;
		virtual void Bind() const override;
		virtual void Unbind() const override;
	private:
		uint32_t m_RendererId;
		Ref<IndexBuffer> m_IndexBuffer;
		std::vector<Ref<Buffer>> m_Buffers;
	};
}