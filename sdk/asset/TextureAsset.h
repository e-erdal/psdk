//
// Created on March 7th 2021 by loanselot1.
//

#pragma once

#include "pch.h"

#include "Asset.h"

#include "graphics/Texture.h"

class TextureAsset : public Asset {
public:
    TextureAsset(){};

    void Init(uint8_t *data, uint32_t dataSize) override {
        m_data = data;
        m_dataSize = dataSize;
    }

    Texture *LoadTexture(bool AA);

    const AssetType GetAssetType() override {
        return AssetType::TEXTURE;
    }

    Texture *m_texture = 0;
    TextureAssetExtendedData m_assetInfo{};
};