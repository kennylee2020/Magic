#pragma once
#include "Magic.h"

namespace Sample {
	class SampleLayer : public Magic::Layer {
	public:
		SampleLayer();
		virtual void OnUpdate() override;
		virtual void OnImGui() override;
		virtual void OnEvent(Magic::Event& e) override;
	private:
		std::shared_ptr<Magic::Buffer> m_Buffer;
		std::shared_ptr<Magic::IndexBuffer> m_IndexBuffer;
		std::shared_ptr<Magic::Texture> m_Texture;
		std::shared_ptr<Magic::Shader> m_PureColorShader;
	};
}