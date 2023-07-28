#include "Buffer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Magic {
	std::shared_ptr<Buffer> Buffer::create(const BufferLayout& layout) {
		return std::make_shared<OpenGLBuffer>(layout);
	}

	std::shared_ptr<IndexBuffer> IndexBuffer::create() {
		return std::make_shared<OpenGLIndexBuffer>();
	}
}