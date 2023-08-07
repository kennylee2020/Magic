#pragma once
#include <string>
#include <memory>

namespace Magic {
	class Texture
	{
	public:
		Texture() = default;
		virtual ~Texture() = default;
		virtual void Bind(uint32_t slot = 0) const = 0;
		virtual void Unbind() const = 0;
		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		Texture2D() = default;
		virtual ~Texture2D() override = default;
	public:
		static Ref<Texture2D> Create(std::string filePath);
		static Ref<Texture2D> Create(int width, int height, uint8_t* data);
	};
}
