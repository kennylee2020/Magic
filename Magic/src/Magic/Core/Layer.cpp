#include "magicpch.h"
#include "Layer.h"

namespace Magic {
	/// <summary>
	//////////////////////////////////// Layer /////////////////////////////////////
	/// </summary>
	Layer::Layer(const std::string& name) : m_Name(name)
	{
	}

	/// <summary>
	//////////////////////////////////// LayerStack ////////////////////////////////
	/// </summary>
	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
		{
			layer->OnDetach();
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.push_back(layer);
		layer->OnAttach();
	}
}