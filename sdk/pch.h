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
// clang-format on

#include "logger/Logger.h"

#include <glm/glm.hpp>