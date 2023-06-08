project "Core"
    kind "StaticLib"
    language "C++"

	targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "cpch.h"
    pchsource "src/cpch.cpp"

    files
    {
        "src/**.h",
        "src/**.cpp",
        "vendor/stb_image/**.*",
        "vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl"
    }

    defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

    includedirs
    {
        "src",
        "vendor/spdlog/include",
        "vendor/glfw/include",
        "vendor/glad/include",
        "vendor/imgui",
        "vendor/stb_image",
        "vendor/glm"
    }

    links
    {
        "glfw",
        "glad",
        "imgui",
        "opengl32.lib"
    }

    filter "system:windows"
		systemversion "latest"

		defines
		{
			"GLFW_INCLUDE_NONE"
		}

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"