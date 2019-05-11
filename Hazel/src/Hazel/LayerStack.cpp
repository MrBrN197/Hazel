#include "hzpch.h"
#include "LayerStack.h"

namespace Hazel {
	LayerStack::LayerStack() {}
	LayerStack::~LayerStack() {
		for (Layer* layer : m_Layers) {
			delete layer;
		}
	}
	
	void LayerStack::PushLayer(Layer* layer){
		m_Layers.emplace(m_Layers.begin() + m_LayerInsterIndex, layer);
		m_LayerInsterIndex++;
	}
	void LayerStack::PushOverlay(Layer* overlay){
		m_Layers.emplace_back(overlay);
	}

	void LayerStack::PopLayer(Layer* layer){
		auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsterIndex, layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LayerInsterIndex--;
		}
	}
	void LayerStack::PopOverlay(Layer* overlay){
		auto it = std::find(m_Layers.begin() + m_LayerInsterIndex, m_Layers.end(), overlay);
		if (it != m_Layers.end())
			m_Layers.erase(it);

	}

}