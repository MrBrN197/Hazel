workspace "Hazel"
	architecture "x64"
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

include "Hazel/vendor/GLFW"
include "Hazel/vendor/Glad"
include "Hazel/vendor/imgui"

project "Hazel"
	location "Hazel"	
	kind "sharedLib"
	language "c++"
	staticruntime "off"

	pchheader "hzpch.h"
	pchsource "Hazel/src/hzpch.cpp"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{includeDir.GLFW}",
		"%{includeDir.Glad}",
		"%{includeDir.ImGui}"
	}

	links{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	defines "HZ_BUILD_DLL"
	
	filter "system:windows"
		cppdialect "c++14"
		systemversion "latest"

		defines {
			"HZ_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/".. outputdir .. "/Sandbox")
		}
	
	filter "configurations:Debug"
		defines "HZ_DEBUG"
		runtime "Debug"
		symbols "On"
	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		optimize "On"
	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		optimize "On"

		
project "Sandbox"
	location "Sandbox"	
	kind "consoleApp"
	language "c++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files{
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.h"
	}

	includedirs{
		"Hazel/vendor/spdlog/include",
		"Hazel/src/"
	}
	links{
		"Hazel"
	}
	
	filter "system:windows"
		cppdialect "c++14"
		systemversion "latest"

		defines "HZ_PLATFORM_WINDOWS"

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		runtime "Debug"
		symbols "On"
	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		optimize "On"
	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		optimize "On"
