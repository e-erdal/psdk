//
// Created on March 7th 2021 by loanselot1.
//

#pragma once

#include "pch.h"

constexpr uint32_t g_assetTag = 1212959812;
constexpr uint16_t g_assetVersion = 0x0001;

enum FileFlags : uint32_t {
    FILE_FLAGS_ENCRYPTED = 1 << 0,
    FILE_FLAGS_COMPRESSED = 1 << 1,
};

enum class AssetType : uint8_t {
    UNKOWNN,
    TEXTURE,
    RAWDATA,
};

#pragma pack(push, 1)
struct TextureAssetExtendedData {
    
    uint32_t width = 0;
    uint32_t height = 0;
    uint8_t channels = 0;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct AssetHeader {
    uint32_t tag = g_assetTag;
    uint16_t version = g_assetVersion;
    uint32_t flags = 0;
    uint32_t originalSize = 0; // for zlib to decompress it

    AssetType type = AssetType::UNKOWNN;
    
    uint32_t specialHeaderSize = 0;
    uint8_t *specialHeader = nullptr;

    uint32_t dataSize = 0;
    uint8_t *data = nullptr;
};
#pragma pack(pop)