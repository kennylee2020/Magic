#pragma once
#include "Texture.h"

#include <filesystem>
#include <artery-font/artery-font.h>

namespace Magic {
	typedef artery_font::Glyph<float> Glyph;

	class Font
	{
	public:
		Font(const std::filesystem::path& fontPath);
		~Font();

		Glyph GetGlyph(uint32_t code);
		Ref<Texture> GetTexture(int index);
		inline void SetFontSize(float size) { m_FontSize = size; }
		inline float GetFontSize() { return m_FontSize; }
		inline float GetScale() { return m_Scale; }
		inline float GetLineHeight() { return m_LineHeight; }
	public:
		static Ref<Font> Create(const std::filesystem::path& fontPath);
	private:
		float m_Scale;
		float m_LineHeight;
		float m_FontSize;
		std::vector<Ref<Texture>> m_Textures;
		std::unordered_map<uint32_t, Glyph> m_Glyphs;
	};
}