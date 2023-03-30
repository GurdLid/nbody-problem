workspace "5BodySim"
    configurations { "Debug", "Release" }
    startproject "5BodySim"

    flags { "MultiProcessorCompile" }

    filter "configurations:Debug"
        defines { "DEBUG", "DEBUG_SHADER" }
        symbols "On"
		runtime "Debug"

    filter "configurations:Release"
        defines { "RELEASE" }
        optimize "on"
        flags { "LinkTimeOptimization" }
		runtime "Release"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "5BodySim"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++latest"
	architecture "x64"

	targetdir("bin/")
	objdir("bin-int/")

    includedirs { "include/", "libs/glad/include/", "libs/glfw/include/", "libs/glm/", "libs/imgui/", "libs/imgui/examples" }
    
    files { "src/*.cpp" }

    links { "GLFW", "GLM", "GLAD", "ImGui" }

    filter "system:linux"
        links { "dl", "pthread" }

        defines { "_X11" }

    filter "system:windows"
        defines { "_WINDOWS" }

include "libs/glfw.lua"
include "libs/glad.lua"
include "libs/glm.lua"
include "libs/imgui.lua"