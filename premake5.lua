workspace "Hazel"
	architecture "x64"
	startproject "Sandbox"
	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

includeDir = {}
includeDir["GLFW"] = "Hazel/vendor/GLFW/include"
includeDir["Glad"] = "Hazel/vendor/Glad/include"
includeDir["ImGui"] = "Hazel/vendor/imgui"
includeDir["glm"] = "Hazel/vendor/glm"

include "Hazel/vendor/GLFW"
include "Hazel/vendor/Glad"
include "Hazel/vendor/imgui"

project "Hazel"
	location "Hazel"	
	kind "StaticLib"
	language "C++"
	cppdialect "C++14"
	staticruntime "on"

	pchheader "hzpch.h"
	pchsource "Hazel/src/hzpch.cpp"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/**.hpp",
		"%{prj.name}/vendor/glm/**.ini"
	}

	includedirs{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{includeDir.GLFW}",
		"%{includeDir.Glad}",
		"%{includeDir.ImGui}",
		"%{includeDir.glm}"
	}

	links{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	defines{
		"_CRT_SECURE_NO_WARNINGS",
		"HZ_BUILD_DLL"
	}
	
	filter "system:windows"
		systemversion "latest"

		defines {
			"HZ_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		runtime "Debug"
		symbols "on"
	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		optimize "on"
	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		optimize "on"

		
project "Sandbox"
	location "Sandbox"	
	kind "consoleApp"
	language "C++"
	cppdialect "C++14"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files{
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.h"
	}

	includedirs{
		"Hazel/vendor/spdlog/include",
		"Hazel/src/",
		"Hazel/vendor",
		"%{includeDir.glm}"
		
	}
	links{
		"Hazel"
	}
	
	filter "system:windows"
		systemversion "latest"
		defines "HZ_PLATFORM_WINDOWS"

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		runtime "Debug"
		symbols "on"
	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		optimize "on"
	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		optimize "on"
