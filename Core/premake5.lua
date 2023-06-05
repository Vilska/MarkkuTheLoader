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
        "src/**.cpp"
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"