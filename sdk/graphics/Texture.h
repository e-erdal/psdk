//
// Created on February 13th 2021 by loanselot1.
//
// Purpose: Main handler for 2D textures.
//

#pragma once

#include "pch.h"

class Texture {
public:
    // AA stands for Anti-Aliasing
    Texture(uint32_t width, uint32_t height, bool AA = false);
    Texture(const std::string &path, bool AA = false);
    ~Texture();

    uint32_t GetWidth() const {
        return m_width;
    }

    uint32_t GetHeight() const {
        return m_height;
    }

    bgfx::TextureHandle &GetHandle() {
        return m_handle;
    }

    void Update(void *data, uint32_t size, uint8_t pitch = 4);

    bool operator==(const Texture &other) const {
        return m_handle.idx == ((Texture &)other).m_handle.idx;
    }

private:
    uint32_t m_width, m_height;
    bgfx::TextureHandle m_handle = BGFX_INVALID_HANDLE;
};