//
// Created on February 11th 2021 by loanselot1.
//
// Purpose:
//

// Idea: Make batch info struct that contains vertices in a vector i guess?
// and then add a map with the texture & vertex info, in flush: loop on
// that map and draw everything.

#pragma once

#include "pch.h"
#include <unordered_map>

#include "graphics/RendererAPI.h"
#include "graphics/Texture.h"

#include <glm/gtc/matrix_transform.hpp>

#include <vector>

static const glm::mat4 g_defPos = { 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1 };
static const glm::mat4x2 g_defCoords = {
    1, 0, //
    1, 1, //
    0, 1, //
    0, 0, //
};

// (vertex)
// vec4[4] =
//     X X X X (X, Y, Z, W)
//     X X X X
//     X X X X
//     X X X X = mat4x4
//
// (uvs)
// vec2[4] =
//     X X . . (U, V)
//     X X . .
//     X X . .
//     X X . . = mat4x2

struct VertexInfo {
    glm::vec2 pos;
    glm::vec2 uvs;
    glm::vec4 color;
    glm::vec2 extra;
};

struct RenderBatcherData {
    std::unordered_map<Texture *, std::vector<VertexInfo>> batchEvents;

    bgfx::VertexLayout defaultLayout;
    bgfx::IndexBufferHandle ibh;

    bgfx::UniformHandle defaultUniform;
    bgfx::ProgramHandle defaultProgram;

    Texture *whiteTexture;

    uint32_t indexes = 0;
};

namespace RenderBatcher {
    void Initialize();

    void NewFrame();
    void EndFrame();
    void Flush();
    void ResetBatch();

    void Submit(Texture *texture, const glm::mat4 &transform, const glm::mat4x2 &uvs, const glm::vec4 &color);

    inline void DrawRectangle(const glm::mat4 &transform, const glm::vec4 &color = { 1, 1, 1, 1 }) {
        Submit(0, transform, g_defCoords, color);    
    }

    inline void DrawRectangle(Texture *texture, const glm::mat4 &transform, const glm::vec4 &color = { 1, 1, 1, 1 }) {
        Submit(texture, transform, g_defCoords, color);    
    }

    Texture *GetWhiteTexture();
} // namespace RenderBatcher
