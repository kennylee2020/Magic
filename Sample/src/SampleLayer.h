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
		Magic::Ref<Magic::Mesh> m_Mesh;
		Magic::Ref<Magic::Texture> m_Texture;
		Magic::Ref<Magic::Shader> m_PureColorShader;
	};
}