#include "magicpch.h"
#include "OpenGLTexture.h"

#include <stb_image.h>
#include <glad/glad.h>

namespace Magic {
	/// <summary>
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////OpenGLTexture2D/////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/// </summary>
	OpenGLTexture2D::OpenGLTexture2D(int width, int height, uint8_t* data) : m_Width(width),m_Height(height)
	{
		glGenTextures(1, &m_RenderId);
		glBindTexture(GL_TEXTURE_2D, m_RenderId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	OpenGLTexture2D::OpenGLTexture2D(std::string filePath)
	{
		int width, height, channel;
		stbi_set_flip_vertically_on_load(true);
		stbi_uc* data = stbi_load(filePath.c_str(), &width, &height, &channel, 0);
		ASSERT(data, "Load texture failed! {0}", filePath);

		GLint format = channel == 3 ? GL_RGB : GL_RGBA;
		GLint internalformat = channel == 3 ? GL_RGB : GL_RGBA;

		glGenTextures(1, &m_RenderId);
		glBindTexture(GL_TEXTURE_2D, m_RenderId);
		glTexImage2D(GL_TEXTURE_2D, 0, internalformat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);

		m_Width = width;
		m_Height = height;
	}

	OpenGLTexture2D::~OpenGLTexture2D() {
		glDeleteTextures(1,&m_RenderId);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_RenderId);
	}

	void OpenGLTexture2D::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	int OpenGLTexture2D::GetWidth() const
	{
		return m_Width;
	}

	int OpenGLTexture2D::GetHeight() const
	{
		return m_Height;
	}
	/// <summary>
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////OpenGLRenderTexture/////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/// </summary>
	OpenGLRenderTexture::OpenGLRenderTexture(Ref<Framebuffer> framebuffer) : m_Framebuffer(framebuffer)
	{

	}
	OpenGLRenderTexture::~OpenGLRenderTexture()
	{
	}

	void OpenGLRenderTexture::Bind(uint32_t slot) const
	{
		uint32_t renderId = m_Framebuffer->GetColorAttachmentRendererID();
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, renderId);
	}

	void OpenGLRenderTexture::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	int OpenGLRenderTexture::GetWidth() const
	{
		return m_Framebuffer->GetWidth();
	}

	int OpenGLRenderTexture::GetHeight() const
	{
		return m_Framebuffer->GetHeight();
	}
}
