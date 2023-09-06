#pragma once
#include "Magic/Graphics/FrameBuffer.h"

namespace Magic {
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferDescriptor& desc);
		virtual ~OpenGLFramebuffer();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void Resize(uint32_t width, uint32_t height) override;
		virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) override;

		virtual void ClearAttachment(uint32_t attachmentIndex, int value) override;
		virtual uint32_t GetColorAttachmentRendererID(uint32_t attachmentIndex = 0) const override;

		virtual int GetWidth() const override { return m_Descriptor.width;}
		virtual int GetHeight() const override { return m_Descriptor.height;}
	private:
		void Rebuild();
	private:
		FramebufferDescriptor m_Descriptor;
		std::vector<FramebufferTextureDescriptor> m_ColorAttachmentDescriptors;
		FramebufferTextureDescriptor m_DepthAttachmentDescriptor;

		uint32_t m_RendererID;
		std::vector<uint32_t> m_ColorAttachments;
		uint32_t m_DepthAttachment;
	};

}