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
		bool OnKeyDownEvent(Magic::KeyDownEvent& e);
	private:
		Magic::Ref<Magic::Framebuffer> m_Framebuffer;
		Magic::Ref<Magic::RenderTexture> m_RenderTexture;
		Magic::Ref<Magic::Material> m_Material;
		Magic::Ref<Magic::Material> m_PostMaterial;
		Magic::Ref<Magic::Scene> m_Scene;
		Magic::Entity m_CameraEntity;
		Magic::Entity m_QuadEntity;
	};
}