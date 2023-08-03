#pragma once
#include "magicpch.h"
#include "Buffer.h"
#include <glm/glm.hpp>

namespace Magic {
	class RendererAPI {
	public:
		enum class API{
			None = 0, OpenGL
		};
	public:
		virtual void Clear() = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void DrawIndexed(const Ref<IndexBuffer>& indexBuffer) = 0;
	public:
		static Ref<RendererAPI> CreateRendererAPI();
		inline static API GetAPI() { return s_API; }
	private:
		static RendererAPI::API s_API;
	};
}