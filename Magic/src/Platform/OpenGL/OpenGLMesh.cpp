#include "OpenGLMesh.h"
#include "glad/glad.h"

namespace Magic {
	OpenGLMesh::OpenGLMesh()
	{
		glGenVertexArrays(1, &m_RendererId);
	}

	OpenGLMesh::~OpenGLMesh()
	{
		glDeleteVertexArrays(1, &m_RendererId);
	}

	void OpenGLMesh::AddBuffer(const BufferLayout& layout, const void* data, uint32_t size)
	{
		glBindVertexArray(m_RendererId);

		Ref<Buffer> buffer = Buffer::Create(layout);
		buffer->SetBufferData(data, size);
		m_Buffers.push_back(buffer);
	}

	void OpenGLMesh::SetIndexBuffer(const uint32_t* data, uint32_t count)
	{
		glBindVertexArray(m_RendererId);

		m_IndexBuffer = IndexBuffer::Create();
		m_IndexBuffer->SetBufferData(data, count);
	}

	void OpenGLMesh::Clear()
	{
		glDeleteVertexArrays(1, &m_RendererId);
		glGenVertexArrays(1, &m_RendererId);
	}

	Ref<IndexBuffer>& OpenGLMesh::GetIndexBuffer()
	{
		return m_IndexBuffer;
	}

	void OpenGLMesh::Bind() const
	{
		glBindVertexArray(m_RendererId);
	}

	void OpenGLMesh::Unbind() const
	{
		glBindVertexArray(0);
	}
}