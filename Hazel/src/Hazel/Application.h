#pragma once
#include "Core.h"

namespace Hazel {
	class HZ_API Application
	{
	public:
		Application();
		virtual ~Application();
		virtual void Run();
	private:

	};
}