#pragma once
#include "Hazel\Core.h"
#include "Hazel\Events\Event.h"

namespace Hazel {
	class Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();


		virtual void OnUpdate() {}
		virtual void OnDetach() {}
		virtual void OnAttach() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;

	};
}