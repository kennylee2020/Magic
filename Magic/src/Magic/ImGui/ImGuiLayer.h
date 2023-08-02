#pragma once

#include "Magic/Core/Layer.h"

namespace Magic {
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer(const std::string& name = "ImGui") : Layer(name) {};
		~ImGuiLayer() = default;
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGui() override;
	public:
		static void BeginImGui();
		static void EndImGui();
	};
}
