#pragma once
#include <string>
#include <vector>

#include "Magic/Event/Event.h"

namespace Magic {
	class Layer {
	public:
		Layer(const std::string& name);
		~Layer() = default;
		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnUpdate() {};
		virtual void OnImGui() {};
		virtual void OnEvent(Event& e) {};
		virtual const std::string& GetName() const {return m_Name;}
	protected:
		std::string m_Name;
	};

	class LayerStack {
	public:
		LayerStack() = default;
		~LayerStack();
		void PushLayer(Layer* layer);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
		std::vector<Layer*>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
		std::vector<Layer*>::reverse_iterator rend() { return m_Layers.rend(); }

		std::vector<Layer*>::const_iterator begin() const { return m_Layers.begin(); }
		std::vector<Layer*>::const_iterator end() const { return m_Layers.end(); }
		std::vector<Layer*>::const_reverse_iterator rbegin() const { return m_Layers.rbegin(); }
		std::vector<Layer*>::const_reverse_iterator rend() const { return m_Layers.rend(); }
	private:
		std::vector<Layer*> m_Layers;
	};
}
