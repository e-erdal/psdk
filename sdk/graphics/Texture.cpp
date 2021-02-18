#include "Texture.h"

#include <stb_image.h>

static uint32_t ApplyTextureFilter(bool AA) {
    return AA ? (BGFX_SAMPLER_NONE) : (BGFX_SAMPLER_MIN_POINT | BGFX_SAMPLER_MAG_POINT);
}

Texture::Texture(uint32_t width, uint32_t height, bool AA) : m_width(width), m_height(height) {
    m_handle = bgfx::createTexture2D((uint16_t)width, (uint16_t)height, false, 1, bgfx::TextureFormat::RGBA8, ApplyTextureFilter(AA), nullptr);

    if (!bgfx::isValid(m_handle))
        DEBUG_LOG_ERROR("Texture is invalid!");
}

Texture::Texture(const std::string &path, bool AA) {
    int width, height, channels;
    stbi_set_flip_vertically_on_load(1);
    stbi_uc *data = 0;
    data = stbi_load(path.c_str(), &width, &height, &channels, 0);

    if (!data) {
        LOG_ERROR("Cannot load %s!", path.c_str());
        return;
    }

    m_width = width;
    m_height = height;

    GLenum internalFormat = 0, dataFormat = 0;
    if (channels == 4) {
        internalFormat = GL_RGBA8;
        dataFormat = GL_RGBA;
    } else if (channels == 3) {
        internalFormat = GL_RGB8;
        dataFormat = GL_RGB;
    }

    auto memory = bgfx::copy(data, (width * height) * channels);
    m_handle = bgfx::createTexture2D((uint16_t)width, (uint16_t)height, false, 1, bgfx::TextureFormat::RGBA8, ApplyTextureFilter(AA), memory);

    if (!bgfx::isValid(m_handle))
        DEBUG_LOG_ERROR("Texture is invalid!");

    stbi_image_free(data);
}

Texture::~Texture() {
    bgfx::destroy(m_handle);
}

void Texture::Update(void *data, uint32_t size, uint8_t pitch) {
    auto memory = bgfx::copy(data, size);
    bgfx::updateTexture2D(m_handle, 0, 0, 0, 0, (uint16_t)m_width, (uint16_t)m_height, memory, (uint16_t)pitch * (uint16_t)m_width);
}