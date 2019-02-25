#pragma once
#include "Hazel\Core.h"
#include "../Layer.h"
#include "../Events/ApplicationEvent.h"
#include "../Events/KeyEvent.h"
#include "../Events/MouseEvent.h"

namespace Hazel {

	class HAZEL_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnDetach() override;
		virtual void OnAttach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

		inline const std::string& GetName() const { return m_DebugName; }
	private:
		float m_Time = 0.0f;
	};
}
