workspace "5BodySim"
    architecture "x64"
    startproject "5BodySim"
    configurations { "Debug", "Release" }
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

include "5BodySim"