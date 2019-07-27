#pragma once

namespace Hazel {

	class Timestep {
	public:
		Timestep(float time = 0.f) : m_Time(time) {

		}

		operator float() {
			return m_Time;
		}

		float GetSeconds() { return m_Time; }
		float GetMilliseconds() { return m_Time * 1000.f; }
	private:
		float m_Time;
	};

}