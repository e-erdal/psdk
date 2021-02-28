//
// Created on February 27th 2021 by loanselot1.
//
// Purpose:
//

#pragma once

#include "pch.h"

struct ItemInfo {
    uint8_t type;
    uint8_t material;
    uint8_t visualEffect;
    uint8_t storage;
    uint8_t textureX;
    uint8_t textureY;
    uint8_t layerDepth;
    uint8_t collisionType;
    uint8_t hardness;
    uint8_t bodyPart;
    uint8_t maxCount;
    uint8_t seedBase;
    uint8_t seedOverlay;
    uint8_t treeBase;
    uint8_t treeLeaves;

    uint16_t flags;
    uint16_t rarity;

    uint32_t ID;
    uint32_t extraStringHash;
    uint32_t animMS; // or leash id
    uint32_t textureHash;
    uint32_t cook;
    uint32_t healTime;
    uint32_t seedColor;
    uint32_t overlayColor;
    uint32_t cooldown;
    uint32_t animFlags;
    uint32_t flags2;
    uint32_t range;
    uint32_t maxStorage;
    uint64_t overlayObject;

    std::string name;
    std::string texture;
    std::string extraString;
    std::string battleName;
    std::string battlePrefix;
    std::string battleSuffix;
    std::string battleAbility;
    std::string idleAnim;
    std::string extraTexture;
    std::string activeAnim;
    std::string customPunchInfo;

    // We are explicitly not initializing member variables here,
    // to save on initialization for the std::vector.
    ItemInfo() {
    }

    ItemInfo(uint8_t* mem, uintptr_t& cur, uint16_t version);
};

struct Items {
    bool isLoaded = false;
    bool isUpdating = false;

    uint8_t *rawData = 0;

    uint16_t version = 0;

    uint32_t count = 0;
    uint32_t rawDataSize = 0;
    uint32_t hash = 0;

    std::vector<ItemInfo> m_Items;

    void Load(uint8_t *mem);

    ItemInfo *Get(uint16_t itemId);
};

extern Items *g_items;