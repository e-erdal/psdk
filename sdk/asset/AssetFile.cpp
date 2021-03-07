#include "AssetFile.h"

#include <filesystem/FileSystem.h>
#include <utils/Memory.h>

void AssetFile::Save(const std::string &path) {
    std::vector<uint8_t> data;

    memory::SerializeIntoVector(header.tag, data);
    memory::SerializeIntoVector(header.version, data);
    memory::SerializeIntoVector(header.flags, data);
    memory::SerializeIntoVector(header.type, data);

    switch (header.type) {
        case AssetType::TEXTURE:
            memory::SerializeIntoVector(header.specialHeaderSize, data);
            memory::SerializeIntoVector(header.specialHeader, data, sizeof(TextureAssetExtendedData));
            break;
        default: break;
    }

    memory::SerializeIntoVector(header.dataSize, data);
    memory::SerializeIntoVector(header.data, data, header.dataSize);

    FileSystem::WriteBinaryFile(path, data.data(), data.size());
}

bool AssetFile::Load(uint8_t *mem, const uint32_t &size) {
    if (size < sizeof(AssetHeader)) {
        LOG_ERROR("Asset manager tried to load invalid file, data is corrupted or not our file. Aborting...");
        DEBUG_LOG_ERROR("File size is too small.");
        free(mem);
        return false;
    }

    uintptr_t pos = 0;

    header.tag = memory::Get<uint32_t>(mem, pos);
    header.version = memory::Get<uint16_t>(mem, pos);
    header.flags = memory::Get<uint32_t>(mem, pos);
    header.originalSize = memory::Get<uint32_t>(mem, pos);
    header.type = memory::Get<AssetType>(mem, pos);

    switch (header.type) {
        case AssetType::TEXTURE:
            header.specialHeaderSize = sizeof(TextureAssetExtendedData);
            memcpy(header.specialHeader, mem + pos, header.specialHeaderSize);
            break;
        default: break;
    }

    header.dataSize = memory::Get<uint32_t>(mem, pos);
    header.data = (uint8_t *)malloc(header.dataSize);
    memcpy(header.data, mem + pos, header.dataSize);

    if (header.tag != g_assetTag) {
        LOG_ERROR("Asset manager tried to load invalid file, data is corrupted or not our file. Aborting...");
        DEBUG_LOG_ERROR("Asset tag is wrong.");
        free(mem);
        return false;
    }

    DEBUG_LOG_INFO("Loaded (type: %d, size: %d)", header.type, header.dataSize);

    free(mem);
    return true;
}

bool AssetFile::Load(const std::string &path) {
    DEBUG_LOG_INFO("Loading %s", path.c_str());
    uint32_t size = 0;
    uint8_t *data = FileSystem::ReadBinaryFile(path.c_str(), &size);
    return Load(data, size);
}