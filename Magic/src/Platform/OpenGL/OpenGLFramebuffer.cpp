#include "magicpch.h"
#include "OpenGLFrameBuffer.h"

#include "glad/glad.h"

namespace Magic {
	static const uint32_t s_MaxFrameBufferSize = 8192;

	namespace Utils {
		static bool IsDepth(FramebufferTextureFormat format) {
			switch (format)
			{
			case FramebufferTextureFormat::DEPTH24STENCIL8: return true;
			}
			return false;
		}

		static GLenum TextureTarget(bool multisampled) {
			return multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
		}

		static void AttachColorTexture(uint32_t id, int samples, GLenum internalFormat, GLenum format, uint32_t width, uint32_t height, int index)
		{
			bool multisampled = samples > 1;
			if (multisampled)
			{
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, internalFormat, width, height, GL_FALSE);

				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_TEXTURE_2D_MULTISAMPLE, id, 0);
			}
			else
			{
				glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_TEXTURE_2D, id, 0);
			}
		}

		static void AttachDepthTexture(uint32_t id, int samples, GLenum internalFormat, GLenum format, GLenum attachmentType, uint32_t width, uint32_t height)
		{
			bool multisampled = samples > 1;
			if (multisampled)
			{
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);

				glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, GL_TEXTURE_2D_MULTISAMPLE, id, 0);
			}
			else
			{
				glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, GL_DEPTH_STENCIL, format, nullptr);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				
				glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, GL_TEXTURE_2D, id, 0);
			}
		}

		static GLenum FramebufferTextureFormatToGLFormat(FramebufferTextureFormat format)
		{
			return Utils::IsDepth(format) ? GL_DEPTH_STENCIL : GL_COLOR;
		}
	}

	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferDescriptor& desc) : m_Descriptor(desc)
	{
		for (auto desc : desc.attachments.attachments)
		{
			if (Utils::IsDepth(desc.format)) {
				m_DepthAttachmentDescriptor = desc;
			}
			else {
				m_ColorAttachmentDescriptors.push_back(desc);
			}
		}
		Rebuild();
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		glDeleteFramebuffers(1, &m_RendererID);
		glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());
		glDeleteTextures(1, &m_DepthAttachment);
	}

	void OpenGLFramebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		glViewport(0, 0, m_Descriptor.width, m_Descriptor.height);
	}

	void OpenGLFramebuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::Resize(uint32_t width, uint32_t height)
	{
		if (width == 0 || height == 0 || width > s_MaxFrameBufferSize || height > s_MaxFrameBufferSize)
		{
			MAG_CORE_WARN("Attempted to rezize framebuffer to {0}, {1}", width, height);
			return;
		}
		m_Descriptor.width = width;
		m_Descriptor.height = height;

		Rebuild();
	}

	int OpenGLFramebuffer::ReadPixel(uint32_t attachmentIndex, int x, int y)
	{
		ASSERT(attachmentIndex < m_ColorAttachments.size(), "Index is outof range!");

		glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);
		int pixelData;
		glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData);
		return pixelData;
	}

	void OpenGLFramebuffer::ClearAttachment(uint32_t attachmentIndex, int value)
	{
		ASSERT(attachmentIndex < m_ColorAttachments.size(), "Index is outof range!");

		auto& desc = m_ColorAttachmentDescriptors[attachmentIndex];
		glClearBufferiv(Utils::FramebufferTextureFormatToGLFormat(desc.format), m_ColorAttachments[attachmentIndex], &value);
	}

	uint32_t OpenGLFramebuffer::GetColorAttachmentRendererID(uint32_t attachmentIndex) const
	{
		ASSERT(attachmentIndex < m_ColorAttachments.size(), "Index is outof range!");
		return m_ColorAttachments[attachmentIndex];
	}

	void OpenGLFramebuffer::Rebuild() {
		if (m_RendererID) {
			glDeleteFramebuffers(1, &m_RendererID);
			glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());
			glDeleteTextures(1, &m_DepthAttachment);

			m_ColorAttachments.clear();
			m_DepthAttachment = 0;
		}

		glGenFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		
		bool multisample = m_Descriptor.samples > 1;
		// Attachments
		if (m_ColorAttachmentDescriptors.size())
		{
			GLenum textureTarget = Utils::TextureTarget(multisample);
			m_ColorAttachments.resize(m_ColorAttachmentDescriptors.size());
			glGenTextures(m_ColorAttachments.size(), m_ColorAttachments.data());
			for (size_t i = 0; i < m_ColorAttachments.size(); i++)
			{
				glBindTexture(textureTarget, m_ColorAttachments[i]);
				switch (m_ColorAttachmentDescriptors[i].format)
				{
				case FramebufferTextureFormat::RGBA8:
					Utils::AttachColorTexture(m_ColorAttachments[i], m_Descriptor.samples, GL_RGBA8, GL_RGBA, m_Descriptor.width, m_Descriptor.height, i);
					break;
				case FramebufferTextureFormat::RED_INTEGER:
					Utils::AttachColorTexture(m_ColorAttachments[i], m_Descriptor.samples, GL_R32I, GL_RED_INTEGER, m_Descriptor.width, m_Descriptor.height, i);
					break;
				default:
					MAG_CORE_ERROR("Unhandle format {0}", (int)m_ColorAttachmentDescriptors[i].format);
				}
			}
		}
		
		if (m_DepthAttachmentDescriptor.format != FramebufferTextureFormat::None)
		{
			GLenum textureTarget = Utils::TextureTarget(multisample);
			glGenTextures(1, &m_DepthAttachment);
			glBindTexture(textureTarget, m_DepthAttachment);
			
			switch (m_DepthAttachmentDescriptor.format)
			{
			case FramebufferTextureFormat::DEPTH24STENCIL8:
				Utils::AttachDepthTexture(m_DepthAttachment, m_Descriptor.samples, GL_DEPTH24_STENCIL8, GL_UNSIGNED_INT_24_8, GL_DEPTH_STENCIL_ATTACHMENT, m_Descriptor.width, m_Descriptor.height);
				break;
			}
		}

		ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}