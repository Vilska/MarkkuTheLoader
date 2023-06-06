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
        "../Core/src"
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