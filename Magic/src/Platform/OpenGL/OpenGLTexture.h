#pragma once

#include "Magic/Graphics/Texture.h"
namespace Magic {
	class OpenGLTexture2D : public Texture2D {
	public:
		OpenGLTexture2D(int width, int height, uint8_t* data);
		OpenGLTexture2D(std::string filePath);
		~OpenGLTexture2D();
		virtual void Bind(uint32_t slot) const override;
		virtual void Unbind() const override;
		virtual int GetWidth() const override;
		virtual int GetHeight() const override;
	private:
		uint32_t m_RenderId;
		int m_Width, m_Height;
	};
}