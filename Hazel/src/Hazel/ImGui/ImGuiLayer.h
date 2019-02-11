#include "Hazel\Core.h"
#include "../Layer.h"

namespace Hazel {

	class HAZEL_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();

		virtual void OnUpdate() override;
		virtual void OnDetach() override;
		virtual void OnAttach() override;
		virtual void OnEvent(Event& event) override;

		inline const std::string& GetName() const { return m_DebugName; }
	private:
		float m_Time = 0.0f;
	};

}