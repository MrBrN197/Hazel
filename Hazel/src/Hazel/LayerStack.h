#pragma once

#include "Hazel\Layer.h"
#include "hzpch.h"

namespace Hazel {
	class HAZEL_API LayerStack {
	public:
		LayerStack();
		~LayerStack();

		void OnUpdate();
		void OnRender();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		inline std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		inline std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:
		std::vector<Layer*> m_Layers;
		std::vector<Layer*>::iterator m_LayerInsert;
	};
}