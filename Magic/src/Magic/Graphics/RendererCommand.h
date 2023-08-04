#pragma once

#include "RendererAPI.h"

namespace Magic {
	class RendererCommand
	{
	public:
		inline static void Init() {
			s_RendererAPI->Init();
		};

		inline static void Clear() {
			s_RendererAPI->Clear();
		};

		inline static void SetClearColor(const glm::vec4& color) {
			s_RendererAPI->SetClearColor(color);
		}

		inline static void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
			s_RendererAPI->SetViewPort(x, y, width, height);
		}

		inline static void DrawIndexed(const Ref<IndexBuffer>& indexBuffer) {
			s_RendererAPI->DrawIndexed(indexBuffer);
		}
	private:
		static Ref<RendererAPI> s_RendererAPI;
	private:
		RendererCommand() = delete;
	};
}