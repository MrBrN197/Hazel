#pragma once

#include "Hazel\Core\Layer.h"
#include "hzpch.h"

namespace Hazel {
	class HAZEL_API LayerStack {
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		inline std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		inline std::vector<Layer*>::iterator end() { return m_Layers.end(); }
		inline std::vector<Layer*>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
		inline std::vector<Layer*>::reverse_iterator rend() { return m_Layers.rend(); }

		inline std::vector<Layer*>::const_iterator begin() const { return m_Layers.cbegin(); }
		inline std::vector<Layer*>::const_iterator end() const { return m_Layers.cend(); }
		inline std::vector<Layer*>::const_reverse_iterator rbegin() const { return m_Layers.crbegin(); }
		inline std::vector<Layer*>::const_reverse_iterator rend() const { return m_Layers.crend(); }

	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex = 0;
	};
}