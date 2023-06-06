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
    group ""

    include "Core"
    include "Sandbox"