#pragma once

#include <memory>

#ifdef HZ_PLATFORM_WINDOWS
	#if HZ_DYNAMIC_BUILD
		#ifdef HZ_BUILD_DLL
			#define HAZEL_API __declspec(dllexport)
		#else
			#define HAZEL_API __declspec(dllimport)
		#endif
	#else
		#define HAZEL_API
#endif
#else
	#error "Hazel supports windows only"
#endif


#define BIT(x) (1 << x)

#if HZ_DEBUG
	#define HZ_ENABLED_ASSERTS
#endif // !HZ_ENABLED_ASSERTS


#ifdef HZ_ENABLED_ASSERTS
	#define	HZ_ASSERT(x, ...) if(!(x)) { HZ_ERROR("Assertion Failure: {0}",__VA_ARGS__); __debugbreak(); }
	#define	HZ_CORE_ASSERT(x, ...) if(!(x)) { HZ_CORE_ERROR("Assertion Failure: {0}",__VA_ARGS__); __debugbreak(); }
#else
	#define HZ_ASSERT(x, ...)
	#define HZ_CORE_ASSERT(x, ...)
#endif

#define HZ_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Hazel {

	template <typename T>
	using Ref = std::shared_ptr<T>;
	template <typename T, typename ... Args>
	Ref<T> CreateRef(Args&& ... args) {
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template <typename T>
	using Scope = std::unique_ptr<T>;
	template <typename T, typename ... Args>
	Scope<T> CreateScope(Args&& ... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
}