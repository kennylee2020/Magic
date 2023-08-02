#include "Buffer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Magic {
	Ref<Buffer> Buffer::Create(const BufferLayout& layout) {
		return CreateRef<OpenGLBuffer>(layout);
	}

	Ref<IndexBuffer> IndexBuffer::Create() {
		return CreateRef<OpenGLIndexBuffer>();
	}
}