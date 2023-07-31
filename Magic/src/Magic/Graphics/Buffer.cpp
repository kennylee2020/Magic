#include "Buffer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Magic {
	std::shared_ptr<Buffer> Buffer::Create(const BufferLayout& layout) {
		return std::make_shared<OpenGLBuffer>(layout);
	}

	std::shared_ptr<IndexBuffer> IndexBuffer::Create() {
		return std::make_shared<OpenGLIndexBuffer>();
	}
}