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
		bool OnWindowResize(Magic::WindowResizeEvent& e);
	private:
		Magic::Ref<Magic::Camera> m_Camera;
		Magic::Ref<Magic::Material> m_Material;
	};
}