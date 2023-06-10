project "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

    includedirs
    {
        "../Core/vendor/spdlog/include",
        "../Core/src",
        "../Core/vendor/glad/include",
        "../Core/vendor/imgui",
        "../Core/vendor/glm",
        "../Core/vendor/assimp/include"
    }

    links
    {
        "Core"
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"