#pragma once
#include "Magic/Graphics/Buffer.h"

namespace Magic {
	class OpenGLBuffer : public Buffer {
	public:
		OpenGLBuffer(const BufferLayout& layout);
		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void SetBufferData(unsigned int size, const void* data) override;
	private:
		void setupBufferLayout(const BufferLayout& layout);
	private:
		unsigned int m_RendererId;
		BufferLayout m_BufferLayout;
	};

	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer();
		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual int GetCount() const override;
		virtual void SetBufferData(unsigned int count, const unsigned int* data) override;
	private:
		unsigned int m_RendererId;
		unsigned int m_Count;
	};
}
