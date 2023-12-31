#pragma once
#include "Magic/Graphics/RendererAPI.h"

namespace Magic {
	class OpenGLRendererAPI : public RendererAPI{
	public:
		virtual ~OpenGLRendererAPI() override = default;
		virtual void Init() override;
		virtual void Clear() override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		virtual void DrawIndexed(const Ref<IndexBuffer>&) override;
	};
}