//
// Created on February 12th 2021 by loanselot1.
//
// Purpose: Pre-compiled header of SDK (library). This will allow us
//          to avoid errors like "OpenGL header already included" bullshit.
//

#pragma once

#define _CRT_SECURE_NO_WARNINGS

// Disable clang format so we can align includes like what we want
// clang-format off
#include <stdint.h>
#include <string>
#include <vector>

#include "Platform.h"
#include "graphics/RendererAPI.h"

#include <GLFW/glfw3.h>
#if PLATFORM_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#endif
#include <GLFW/glfw3native.h>

// clang-format on

#include "logger/Logger.h"

#include <glm/glm.hpp>

#define MAKE_RGBA(r, g, b, a) (((uint32_t)(r) << 24) + ((uint32_t)(g) << 16) + ((uint32_t)(b) << 8) + ((uint32_t)(a)))

constexpr unsigned g_MaxVBCount = 134217728;