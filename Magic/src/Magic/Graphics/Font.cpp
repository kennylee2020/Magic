#include "magicpch.h"
#include "Font.h"

#include <artery-font/std-artery-font.h>
#include <artery-font/stdio-serialization.h>
#include <stb_image.h>

/// <summary>
/// I have tried use msdf as a library,but there are so many stuff have to do.
/// So I use generated artery font eventually!
/// Command line: msdf-atlas-gen.exe -font BitterPro-Regular.ttf -arfont test.arfont -format png
/// https://github.com/Chlumsky/msdf-atlas-gen/blob/master/msdf-atlas-gen/artery-font-export.cpp
/// https://learnopengl.com/In-Practice/Text-Rendering
/// https://www.websiteplanet.com/blog/best-free-fonts/
/// </summary>

namespace Magic {
	Ref<Font> Font::Create(const std::filesystem::path& fontPath)
	{
		return CreateRef<Font>(fontPath);
	}

	Font::Font(const std::filesystem::path& fontPath)
	{
		artery_font::StdArteryFont<float> font;
		if (!artery_font::readFile(font, fontPath.string().c_str())) {
			MAG_CORE_ERROR("Load font {0} failed!");
			return;
		}

		auto imgs = font.images;
		for (int i = 0; i < imgs.length(); i++) {
			auto img = imgs[i];
			int width, height, channel;
			stbi_set_flip_vertically_on_load(true);
			stbi_uc* data = stbi_load_from_memory((unsigned char *)img.data, img.data.length(), &width, &height, &channel, 0);
			auto texture = Texture2D::Create(width, height, data);
			m_Textures.push_back(texture);
			stbi_image_free(data);
		}

		auto variants = font.variants;
		for (int i = 0; i < variants.length(); i++) {
			auto variant = variants[i];
			m_FontSize = variant.metrics.fontSize;
			m_Scale = 1.0f / (variant.metrics.ascender - variant.metrics.descender);
			m_LineHeight = variant.metrics.lineHeight;
			
			auto glyphs = variant.glyphs;
			for (int j = 0; j < glyphs.length(); j++) {
				auto glyph = glyphs[j];
				m_Glyphs[glyph.codepoint] = glyph;
			}
		}
	}

	Font::~Font()
	{
	}

	Ref<Texture> Font::GetTexture(int index) {
		if (index < 0 || index >= m_Textures.size()) {
			MAG_CORE_ERROR("Index out of range!");
			return nullptr;
		}
		return m_Textures[index];
	}

	Glyph Font::GetGlyph(uint32_t code) {
		if (m_Glyphs.find(code) != m_Glyphs.end()) {
			return m_Glyphs.at(code);
		}
		return {};
	}
}