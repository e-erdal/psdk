#include "MainMenu.h"

#include "asset/AssetFile.h"
#include "asset/TextureAsset.h"

#include "filesystem/FileSystem.h"

Entity *MainMenuCreate(Entity *parent) {
    Entity *bg = parent->AddEntity(new Entity);

    uint32_t size = 0;
    uint8_t *data = FileSystem::ReadBinaryFile("test.png", &size);

    auto file = new AssetFile();
    auto af = new TextureAsset();

    af->Init(data, size);
    af->m_assetType = AssetType::TEXTURE;
    af->m_assetInfo.width = 1024;
    af->m_assetInfo.height = 1024;
    af->m_assetInfo.channels = 5;
    file->SetContent(af);
    file->Save("test.dat");

    return bg;
}