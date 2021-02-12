//
// Created on February 12th 2021 by loanselot1.
//
// Purpose: This is an api that lets us to jump between graphics libraries.
//          For example we can jump between libraries with defined macros below.
//          This also lets us to use one function for every api, basically little abstraction
//

#pragma once

#define CURRENT_API_OPENGL 1
#define CURRENT_API_BGFX 0

#if CURRENT_API_OPENGL
#include <glad/glad.h>
#elif CURRENT_API_BGFX
#endif

class Window; // no clue if this is good or not, i hope i wont get linker shit while dealing this this
class RendererAPI {
public:
    static bool Initialize(Window *wapi);

    // rendering functions
    static void DrawArrays();

    // viewport functions
    static void ResetView(int32_t width, int32_t height);

private:
};