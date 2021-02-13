#include "Texture.h"

#include <stb_image.h>

Texture::Texture(uint32_t width, uint32_t height, bool AA) : m_width(width), m_height(height) {
    glCreateTextures(GL_TEXTURE_2D, 1, &m_idx);
    glTextureStorage2D(m_idx, 1, GL_RGBA8, m_width, m_height);

    glTextureParameteri(m_idx, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(m_idx, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTextureParameteri(m_idx, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(m_idx, GL_TEXTURE_WRAP_T, GL_REPEAT);
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

    glCreateTextures(GL_TEXTURE_2D, 1, &m_idx);
    glTextureStorage2D(m_idx, 1, internalFormat, m_width, m_height);

    glTextureParameteri(m_idx, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(m_idx, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTextureParameteri(m_idx, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(m_idx, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTextureSubImage2D(m_idx, 0, 0, 0, m_width, m_height, dataFormat, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
}

Texture::~Texture() {
    glDeleteTextures(1, &m_idx);
}

void Texture::SetData(void *data, uint32_t size, uint8_t pitch) {
    glTextureSubImage2D(m_idx, 0, 0, 0, m_width, m_height, pitch, GL_UNSIGNED_BYTE, data);
}

void Texture::Bind(uint32_t slot) const {
    glBindTextureUnit(slot, m_idx);
}