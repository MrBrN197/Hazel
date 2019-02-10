#pragma once
#ifdef HZ_PLATFORM_WINDOWS
	#ifdef HZ_BUILD_DLL
		#define HAZEL_API __declspec(dllexport)
	#else
		#define HAZEL_API __declspec(dllimport)
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
