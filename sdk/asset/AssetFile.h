//
// Created on March 7th 2021 by loanselot1.
//

#pragma once

#include "pch.h"

#include "AssetHeader.h"
#include "TextureAsset.h"

#include "utils/Memory.h"

struct AssetFile {
    AssetHeader header;

    template <typename T>
    T *Get() {
        auto asset = new T();
        asset->Init(header.data, header.dataSize);

        switch (asset->GetAssetType()) {
            //case AssetType::TEXTURE: header.extendedData = ((TextureAsset *)asset)->m_assetInfo; break;
            default: break;
        }

        return asset;
    }

    template <typename TAsset>
    void SetContent(TAsset *asset, uint32_t flags = 0) {
        header.type = asset->GetAssetType();
        header.flags = flags;

        switch (header.type) {
            case AssetType::TEXTURE: {
                TextureAssetExtendedData ext{};

                if (((TextureAsset *)asset)->m_texture) {
                    ext.width = ((TextureAsset *)asset)->m_texture->GetWidth();
                    ext.height = ((TextureAsset *)asset)->m_texture->GetHeight();
                    ext.channels = 4;
                }

                header.specialHeaderSize = sizeof(TextureAssetExtendedData);
                header.specialHeader = (uint8_t *)malloc(sizeof(TextureAssetExtendedData));
                memcpy(header.specialHeader, &ext, sizeof(TextureAssetExtendedData));
                break;
            }

            default: break;
        }

        header.data = asset->Data();
        header.dataSize = asset->DataSize();
    }

    void Save(const std::string &path);
    bool Load(const std::string &path);
    bool Load(uint8_t *data, const uint32_t &size);

    void Reset() {
        if (header.data)
            free(header.data);

        if (header.specialHeader)
            free(header.specialHeader);

        header.dataSize = 0;
        header.specialHeaderSize = 0;

        header.type = AssetType::UNKOWNN;
        header.flags = 0;
        header.originalSize = 0;
    }

    ~AssetFile() {
        Reset();
    }
};