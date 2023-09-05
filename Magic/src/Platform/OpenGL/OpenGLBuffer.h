#pragma once
#include "Magic/Graphics/Buffer.h"

namespace Magic {
	class OpenGLBuffer : public Buffer {
	public:
		OpenGLBuffer(const BufferLayout& layout);
		virtual ~OpenGLBuffer() override;
		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void SetBufferData(const void* data,uint32_t size) override;
	private:
		void setupBufferLayout(const BufferLayout& layout);
	private:
		unsigned int m_RendererId;
		BufferLayout m_BufferLayout;
	};

	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer();
		virtual ~OpenGLIndexBuffer() override;
		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual uint32_t GetCount() const override;
		virtual void SetBufferData(const uint32_t* data, uint32_t size) override;
	private:
		uint32_t m_RendererId;
		uint32_t m_Count;
	};

	class OpenGLUniformBuffer : public UniformBuffer {
	public:
		OpenGLUniformBuffer(uint32_t size, uint32_t binding);
		virtual ~OpenGLUniformBuffer();
		virtual void SetBufferData(const void* data, uint32_t size, uint32_t offset = 0) override;
	private:
		uint32_t m_RendererID;
	};
}
