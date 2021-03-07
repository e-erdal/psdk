#include "TextureAsset.h"

Texture *TextureAsset::LoadTexture(bool AA) {
    if (m_texture)
        return m_texture;
    else {
        m_texture = new Texture(m_assetInfo.width, m_assetInfo.height, m_data, AA);
        return m_texture;
    }
}