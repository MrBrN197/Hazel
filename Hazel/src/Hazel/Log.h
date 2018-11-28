#pragma once
#include "Core.h"
#include "spdlog\spdlog.h"
#include <memory>

namespace Hazel {
	class HAZEL_API Log {
	public:
		inline static std::shared_ptr<spdlog::logger> getClientLogger() { return clientLogger; }
		inline static std::shared_ptr<spdlog::logger> getCoreLogger() { return coreLogger; }
		static void Init();
	private:
		static std::shared_ptr<spdlog::logger> clientLogger;
		static std::shared_ptr<spdlog::logger> coreLogger;
	};

}