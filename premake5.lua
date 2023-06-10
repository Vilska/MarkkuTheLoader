workspace "Markku"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release"
    }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    group "Dependencies"
        include "Core/vendor/glfw"
        include "Core/vendor/glad"
        include "Core/vendor/imgui"
        include "Core/vendor/assimp"
    group ""

    include "Core"
    include "Sandbox"