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

include "Hazel/vendor/GLFW"

project "Hazel"
	location "Hazel"	
	kind "sharedLib"
	language "c++"


	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{includeDir.GLFW}"
	}
	links{
		"GLFW",
		"opengl32.lib"
	}

	pchheader "hzpch.h"
	pchsource "Hazel/src/hzpch.cpp"


	defines "HZ_BUILD_DLL"
	
	
	filter "system:windows"
		cppdialect "c++14"
		staticruntime "On"
		systemversion "latest"

		defines "HZ_PLATFORM_WINDOWS"

		postbuildcommands{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/".. outputdir .. "/Sandbox")
		}
	
	filter "configurations:Debug"
		defines "HZ_DEBUG"
		symbols "On"
	filter "configurations:Release"
		defines "HZ_RELEASE"
		optimize "On"
	filter "configurations:Dist"
		defines "HZ_DIST"
		optimize "On"

		
project "Sandbox"
	location "Sandbox"	
	kind "consoleApp"
	language "c++"

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
		staticruntime "On"
		systemversion "latest"

		defines "HZ_PLATFORM_WINDOWS"

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		symbols "On"
	filter "configurations:Release"
		defines "HZ_RELEASE"
		optimize "On"
	filter "configurations:Dist"
		defines "HZ_DIST"
		optimize "On"
