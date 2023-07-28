#include "OpenGLBuffer.h"

#include "glad/glad.h"

namespace Magic {
	static GLenum shaderDataType2GLenum(const ShaderDataType type) {
		switch (type)
		{
		case Magic::ShaderDataType::None:	return GL_NONE;
		case Magic::ShaderDataType::Bool:	return GL_BOOL;
		case Magic::ShaderDataType::Int:	return GL_INT;
		case Magic::ShaderDataType::Int2:	return GL_INT;
		case Magic::ShaderDataType::Int3:	return GL_INT;
		case Magic::ShaderDataType::Int4:	return GL_INT;
		case Magic::ShaderDataType::Float:	return GL_FLOAT;
		case Magic::ShaderDataType::Float2:	return GL_FLOAT;
		case Magic::ShaderDataType::Float3:	return GL_FLOAT;
		case Magic::ShaderDataType::Float4:	return GL_FLOAT;
		}
		MAG_ERROR_CORE("Unknown ShaderDataType {0}", 0);
	}
	
	/// <summary>
	/// ////////////////////////////////// OpenGLBuffer ///////////////////////////////
	/// </summary>
	OpenGLBuffer::OpenGLBuffer(const BufferLayout& layout) : m_BufferLayout(layout){
		glGenBuffers(1, &m_RendererId);
	}

	void OpenGLBuffer::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
	}

	void OpenGLBuffer::unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLBuffer::setBufferData(unsigned int size, const void* data)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		setupBufferLayout(m_BufferLayout);
	}

	void OpenGLBuffer::setupBufferLayout(const BufferLayout& layout) {
		int index = 0, stride = layout.getStride();
		std::vector <BufferLayout::LayoutRow> layouts = layout.getLayouts();
		for (BufferLayout::LayoutRow& row : layouts) {
			GLenum glEnum = shaderDataType2GLenum(row.type);
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, row.dimension, glEnum, row.normalized ? GL_TRUE : GL_FALSE, stride, (void*)(row.offset));
			index++;
		}
	}

	/// <summary>
	/// ////////////////////////////////// OpenGLIndexBuffer /////////////////////////////
	/// </summary>
	OpenGLIndexBuffer::OpenGLIndexBuffer() : m_Count(0)
	{
		glGenBuffers(1, &m_RendererId);
	}

	void OpenGLIndexBuffer::bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
	}

	void OpenGLIndexBuffer::unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	int OpenGLIndexBuffer::getCount() const
	{
		return m_Count;
	}

	void OpenGLIndexBuffer::setBufferData(unsigned int count, const unsigned int* data)
	{
		m_Count = count;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * count, data, GL_STATIC_DRAW);
	}
}