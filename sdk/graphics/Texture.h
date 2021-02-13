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

    uint32_t GetID() const {
        return m_idx;
    }

    // TODO: make "GetHandle" for BGFX texture.

    void SetData(void *data, uint32_t size, uint8_t pitch = 4);

    void Bind(uint32_t slot = 0) const;

    bool operator==(const Texture &other) const {
        return m_idx == ((Texture &)other).m_idx;
    }

private:
    uint32_t m_width, m_height;
    uint32_t m_idx;
};