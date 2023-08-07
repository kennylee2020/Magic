#pragma once
#include "Magic/Core/Base.h"
#include "Buffer.h"

namespace Magic {
	class Mesh
	{
	public:
		virtual ~Mesh() = default;
		virtual void AddBuffer(const BufferLayout& layout, const void* data, uint32_t size) = 0;
		virtual void SetIndexBuffer(const uint32_t* data, uint32_t count) = 0;
		virtual void Clear() = 0;
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual Ref<IndexBuffer>& GetIndexBuffer() = 0;
	public:
		static Ref<Mesh> Cube;
		static void Init();
		static Ref<Mesh> Create();
	};
}
