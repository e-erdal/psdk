//
// Created on February 12th 2021 by loanselot1.
//
// Purpose: Platform specific defines/vars we needed for cross platform.
//

#pragma once

// clang-format off
#define PLATFORM_ANDROID    0
#define PLATFORM_BSD        0
#define PLATFORM_EMSCRIPTEN 0
#define PLATFORM_HAIKU      0
#define PLATFORM_HURD       0
#define PLATFORM_IOS        0
#define PLATFORM_LINUX      0
#define PLATFORM_NX         0
#define PLATFORM_OSX        0
#define PLATFORM_PS4        0
#define PLATFORM_RPI        0
#define PLATFORM_WINDOWS    0
#define PLATFORM_WINRT      0
#define PLATFORM_XBOXONE    0

#if defined(_DURANGO) || defined(_XBOX_ONE)
    #undef PLATFORM_XBOXONE
    #define PLATFORM_XBOXONE 1
#elif defined(_WIN32) || defined(_WIN64)
    #ifndef NOMINMAX
        #define NOMINMAX
    #endif

    #if defined(_MSC_VER) && (_MSC_VER >= 1700) && (!_USING_V110_SDK71_)
        #include <winapifamily.h>
    #endif // defined(_MSC_VER) && (_MSC_VER >= 1700) && (!_USING_V110_SDK71_)

    #if !defined(WINAPI_FAMILY) || (WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP)
        #undef PLATFORM_WINDOWS

        #if !defined(WINVER) && !defined(_WIN32_WINNT)
            #if ARCH_64BIT
                // When building 64-bit target Win7 and above.
                #define WINVER 0x0601
                #define _WIN32_WINNT 0x0601
            #else
                // Windows Server 2003 with SP1, Windows XP with SP2 and above
                #define WINVER 0x0502
                #define _WIN32_WINNT 0x0502
            #endif // ARCH_64BIT
        #endif // !defined(WINVER) && !defined(_WIN32_WINNT)

    #define PLATFORM_WINDOWS _WIN32_WINNT

    #else
        #undef PLATFORM_WINRT
        #define PLATFORM_WINRT 1
    #endif

#elif defined(__ANDROID__)
    // Android compiler defines __linux__
    #include <sys/cdefs.h> // Defines __BIONIC__ and includes android/api-level.h
    #undef PLATFORM_ANDROID
    #define PLATFORM_ANDROID __ANDROID_API__
#elif defined(__VCCOREVER__)
    // RaspberryPi compiler defines __linux__
    #undef PLATFORM_RPI
    #define PLATFORM_RPI 1
#elif defined(__linux__)
    #undef PLATFORM_LINUX
    #define PLATFORM_LINUX 1
#elif defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__) || defined(__ENVIRONMENT_TV_OS_VERSION_MIN_REQUIRED__)
    #undef PLATFORM_IOS
    #define PLATFORM_IOS 1
#elif defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__)
    #undef PLATFORM_OSX
    #define PLATFORM_OSX __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__
#elif defined(__EMSCRIPTEN__)
    #undef PLATFORM_EMSCRIPTEN
    #define PLATFORM_EMSCRIPTEN 1
#elif defined(__ORBIS__)
    #undef PLATFORM_PS4
    #define PLATFORM_PS4 1
#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__DragonFly__)
    #undef PLATFORM_BSD
    #define PLATFORM_BSD 1
#elif defined(__GNU__)
    #undef PLATFORM_HURD
    #define PLATFORM_HURD 1
#elif defined(__NX__)
    #undef PLATFORM_NX
    #define PLATFORM_NX 1
#elif defined(__HAIKU__)
    #undef PLATFORM_HAIKU
    #define PLATFORM_HAIKU 1
#endif
// clang-format on

// ENTRY POINT CONFIG
#define CONSOLEAPP 0
#define ENTRY_POINT_TYPE int
#define ENTRY_POINT_NAME main
#define ENTRY_POINT_ARGS

#if !CONSOLEAPP

#if PLATFORM_WINDOWS
#include <Windows.h>
#undef ENTRY_POINT_NAME
#undef ENTRY_POINT_ARGS

#define ENTRY_POINT_NAME WINAPI wWinMain
#define ENTRY_POINT_ARGS HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow
#endif

#define ENTRY_POINT() ENTRY_POINT_TYPE ENTRY_POINT_NAME(ENTRY_POINT_ARGS)

#endif
/////////////////////////////