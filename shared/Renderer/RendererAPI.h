//
// Created on February 12th 2021 by loanselot1.
//
// Purpose: This is an api that lets us to jump between graphics libraries.
//          For example we can jump between libraries with defined macros below.
//          This also lets us to use one function for every api, basically little abstraction
//

#define CURRENT_API_OPENGL 1
#define CURRENT_API_BGFX 0

#if CURRENT_API_OPENGL
#include <glad/glad.h>
#elif CURRENT_API_BGFX
#endif

#pragma once

class RendererAPI {
public:
    static bool Initialize();

    // rendering functions

    // viewport functions
    static void ResetView(int32_t width, int32_t height);
};