workspace "GameEngine"
	architecture "x86_64"
	startproject "TestGame"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

	flags {
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

includeDir = {}
includeDir["GLFW"] = "GameEngine/external/GLFW/include"
includeDir["Glad"] = "GameEngine/external/Glad/include"
includeDir["imgui"] = "GameEngine/external/imgui"
includeDir["glm"] = "GameEngine/external/glm"
includeDir["stb_image"] = "GameEngine/external/stb_image"
includeDir["PhysicsEngine"] = "GameEngine/external/PhysicsEngine/src"

group "Dependencies"
	include "GameEngine/external/GLFW"
	include "GameEngine/external/Glad"
	include "GameEngine/external/imgui"
	include "GameEngine/external/PhysicsEngine"
group ""

project "GameEngine" 
	location "GameEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "gepch.h"
	pchsource "GameEngine/src/gepch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/external/stb_image/**.h",
		"%{prj.name}/external/stb_image/**.cpp",
		"%{prj.name}/external/glm/glm/**.hpp",
		"%{prj.name}/external/glm/glm/**.inl",
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/external/spdlog/include",
		"%{includeDir.GLFW}",
		"%{includeDir.Glad}",
		"%{includeDir.imgui}",
		"%{includeDir.glm}",
		"%{includeDir.stb_image}",
		"%{includeDir.PhysicsEngine}"
	}

	links {
		"GLFW",
		"Glad",
		"imgui",
		"opengl32.lib",
		"PhysicsEngine"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"SF_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "SF_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "SF_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "SF_DIST"
		runtime "Release"
		optimize "on"

project "TestGame"
	location "TestGame"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs {
		"GameEngine/external/spdlog/include",
		"GameEngine/src",
		"GameEngine/external",
		"%{includeDir.glm}"
	}

	links {
		"GameEngine"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "SF_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "SF_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "SF_DIST"
		runtime "Release"
		optimize "on"
