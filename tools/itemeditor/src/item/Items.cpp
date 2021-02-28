#include "Items.h"

#include "utils/Memory.h"

Items *g_items = 0;

ItemInfo::ItemInfo(uint8_t *mem, uintptr_t &cur, uint16_t version) {
    ID = Memory::Get<uint32_t>(mem, cur);
    flags = Memory::Get<uint16_t>(mem, cur);
    type = Memory::Get<uint8_t>(mem, cur);
    material = Memory::Get<uint8_t>(mem, cur);

    m_Name = Memory::SerializeStr16(mem, cur);
    if (version > 2) {
        Memory::Unscramble(m_Name, m_ID, Xor("PBG892FXX982ABC*"));
    }
    m_Texture = Memory::GetString(mem, cur);
    m_TextureHash = Memory::Get<uint32_t>(mem, cur);
    m_VisualEffect = Memory::Get<uint8_t>(mem, cur);
    m_Cook = Memory::Get<uint32_t>(mem, cur);
    m_PosX = Memory::Get<uint8_t>(mem, cur);
    m_PosY = Memory::Get<uint8_t>(mem, cur);

    m_Storage = Memory::Get<uint8_t>(mem, cur);
    m_Layer = Memory::Get<uint8_t>(mem, cur);
    m_CollisionType = Memory::Get<uint8_t>(mem, cur);
    m_HitsToDestroy = Memory::Get<uint8_t>(mem, cur);
    m_HealTime = Memory::Get<uint32_t>(mem, cur);
    m_BodyPart = Memory::Get<uint8_t>(mem, cur);
    m_Rarity = Memory::Get<uint16_t>(mem, cur);
    m_MaxCount = Memory::Get<uint8_t>(mem, cur);
    m_ExtraString = Memory::GetString(mem, cur);
    m_ExtraStringHash = Memory::Get<uint32_t>(mem, cur);

    m_AnimMsOrLeashID = Memory::Get<uint32_t>(mem, cur);
    if (version > 3) {
        m_BattleName = Memory::GetString(mem, cur);
        m_BattlePrefix = Memory::GetString(mem, cur);
        m_BattleSuffix = Memory::GetString(mem, cur);
        if (version > 4) {
            m_BattleAbility = Memory::GetString(mem, cur);
        }
    }
    m_SeedBase = Memory::Get<uint8_t>(mem, cur);
    m_SeedOverlay = Memory::Get<uint8_t>(mem, cur);
    m_TreeBase = Memory::Get<uint8_t>(mem, cur);
    m_TreeLeaves = Memory::Get<uint8_t>(mem, cur);
    m_SeedColor = Memory::Get<uint32_t>(mem, cur);
    m_OverlayColor = Memory::Get<uint32_t>(mem, cur);

    //actually the 2 ingredients for this item (as 2x shorts) are here,
    //but removed in new items.dat versions, so skipping
    cur += 4;

    m_ReadyIn = Memory::Get<uint32_t>(mem, cur);
    if (version > 6) {
        m_AnimFlags = Memory::Get<uint32_t>(mem, cur);
        m_IdleAnim = Memory::GetString(mem, cur);
    }
    if (version > 7) {
        m_ExtraTexture = Memory::GetString(mem, cur);
        m_ActiveAnim = Memory::GetString(mem, cur);
        m_OverlayObject = Memory::Get<uint64_t>(mem, cur);
    }
    if (version > 8) {
        m_Flags2 = Memory::Get<uint32_t>(mem, cur);
        cur += 60;
    }

    if (version > 9) {
        m_Range = Memory::Get<uint32_t>(mem, cur);
        m_MaxStorage = Memory::Get<uint32_t>(mem, cur);
    }
    if (version > 10) {
        m_CustomPunchInfo = Memory::GetString(mem, cur);
    }
    if (version > 11) {
        cur += 13;
    }
}