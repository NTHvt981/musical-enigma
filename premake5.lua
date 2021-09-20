workspace "RookGameFramework"
    configurations {"Debug", "Release"}
    platforms { "Win32", "Win64" }
    location "prj"
    
    filter { "platforms:Win32" }
        system "Windows"
        architecture "x86"

    filter { "platforms:Win64" }
        system "Windows"
        architecture "x64"

    --main project
project "GameImpl"
    kind "WindowedApp"
    language "C++"
    files {"GameImpl/**.cpp", "GameImpl/**.h", "GameImpl/**.png"}
    configuration "windows"
        links {"RGFLib", "d3d9", "dxguid", "dxerr", "dinput8", "Dxguid", "dsound", "legacy_stdio_definitions", "avrt", "ole32", "winmm", "d3dx9"}
    includedirs { "RGFLib", "GameImpl" }

    includedirs { "_DXDSDK/Include" }
    filter { "platforms:Win32" }
        libdirs { "_DXDSDK/Lib/x86" }
        targetdir "build/x86"
    filter { "platforms:Win64" }
        libdirs { "_DXDSDK/Lib/x64" }
        targetdir "build/x64"

    --RGF (Rook Game framework) lib
project "RGFLib"
    kind "StaticLib"
    language "C++"
    files {"RGFLib/**.cpp", "RGFLib/**.h"}
    configuration "windows"
        links {"d3d9", "dxguid", "dxerr", "dinput8", "Dxguid", "dsound", "legacy_stdio_definitions", "avrt", "ole32", "winmm", "d3dx9"}
    includedirs { "RGFLib" }

    includedirs { "_DXDSDK/Include" }
    filter { "platforms:Win32" }
        libdirs { "_DXDSDK/Lib/x86" }
        targetdir "build/x86"
    filter { "platforms:Win64" }
        libdirs { "_DXDSDK/Lib/x64" }
        targetdir "build/x64"