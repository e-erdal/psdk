//
// Created on March 7th 2021 by loanselot1.
//

#pragma once

#include "pch.h"

#include "AssetHeader.h"

class Asset {
public:
    Asset(){};
    ~Asset() {
        free(m_data);
        m_dataSize = 0;
    }

public:
    virtual void Init(uint8_t *data, uint32_t dataSize) = 0;

public:
    uint8_t *Data() const {
        return m_data;
    }

    const uint32_t &DataSize() const {
        return m_dataSize;
    }

    virtual const AssetType GetAssetType() = 0;

    AssetType m_assetType = AssetType::UNKOWNN;

    uint8_t *m_data = 0;
    uint32_t m_dataSize = 0;
};