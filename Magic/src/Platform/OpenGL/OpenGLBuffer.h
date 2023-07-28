#pragma once
#include "Magic/Graphics/Buffer.h"

namespace Magic {
	class OpenGLBuffer : public Buffer {
	public:
		OpenGLBuffer(const BufferLayout& layout);
		virtual void bind() const override;
		virtual void unbind() const override;
		virtual void setBufferData(unsigned int size, const void* data) override;
	private:
		void setupBufferLayout(const BufferLayout& layout);
	private:
		unsigned int m_RendererId;
		BufferLayout m_BufferLayout;
	};

	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer();
		virtual void bind() const override;
		virtual void unbind() const override;
		virtual int getCount() const override;
		virtual void setBufferData(unsigned int count, const unsigned int* data) override;
	private:
		unsigned int m_RendererId;
		unsigned int m_Count;
	};
}
