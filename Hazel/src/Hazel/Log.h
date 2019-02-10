#pragma once
#include "Core.h"
#include "spdlog\spdlog.h"
#include "spdlog\fmt\ostr.h"


namespace Hazel {
	class HAZEL_API Log {
	public:
		inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return clientLogger; }
		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return coreLogger; }
		static void Init();
	private:
		static std::shared_ptr<spdlog::logger> clientLogger;
		static std::shared_ptr<spdlog::logger> coreLogger;
	};
}

#define HZ_CORE_TRACE(...)  ::Hazel::Log::getCoreLogger()->trace(__VA_ARGS__)
#define HZ_CORE_INFO(...)	::Hazel::Log::getCoreLogger()->info(__VA_ARGS__)
#define HZ_CORE_WARN(...)	::Hazel::Log::getCoreLogger()->warn(__VA_ARGS__)
#define HZ_CORE_ERROR(...)	::Hazel::Log::getCoreLogger()->error(__VA_ARGS__)
#define HZ_CORE_FATAL(...)  ::Hazel::Log::getCoreLogger()->critical(__VA_ARGS__)

#define HZ_TRACE(...)::Hazel::Log::getClientLogger()->trace(__VA_ARGS__)
#define HZ_INFO(...) ::Hazel::Log::getClientLogger()->info(__VA_ARGS__)
#define HZ_WARN(...) ::Hazel::Log::getClientLogger()->warn(__VA_ARGS__)
#define HZ_ERROR(...)::Hazel::Log::getClientLogger()->error(__VA_ARGS__)
#define HZ_FATAL(...)::Hazel::Log::getClientLogger()->critical(__VA_ARGS__)