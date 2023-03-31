project "5BodySim"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++latest"
    staticruntime "on"

	targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../obj/" .. outputdir .. "/%{prj.name}")

    includedirs { "include/", "../libs/glad/include/", "../libs/glfw/include/", "../ibs/glm/", "../libs/imgui/", "../libs/imgui/examples" }
    
    files { "src/*.cpp" }

    links { "GLFW", "GLM", "GLAD", "ImGui" }

    filter "system:linux"
        links { "dl", "pthread" }

        defines { "_X11" }

    filter "system:windows"
        defines { "_WINDOWS" }

include "../libs/glfw.lua"
include "../libs/glad.lua"
include "../libs/glm.lua"
include "../libs/imgui.lua"