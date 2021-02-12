//
// Created on February 12th 2021 by loanselot1.
//
// Purpose: Magical stuff that you can store multiple data in one param. How amazing?
//

#pragma once

#include <stdint.h>

#include <string>

#define VARIANT_COUNT 10

enum class VariantType : uint8_t {
    NONE,
    FLOAT,
    STRING,
    VECTOR2,
    VECTOR3,
    UINT32,
    ENTITY,
    COMPONENT,
    RECT,
    INT32,
};

#define PREPARE_TYPE(type)                 \
    Variant &operator=(const type &param); \
    type &Get() const

struct Variant {
    // types
    Variant &operator=(const float &param);
    float &GetFloat() const;

    Variant &operator=(const std::string &param);
    std::string Get() const;
    //PREPARE_TYPE(math::vec2);
    //PREPARE_TYPE(math::vec3);
    Variant &operator=(const uint32_t &param);
    uint32_t &GetUInt() const;
    Variant &operator=(const int32_t &param);
    int32_t &GetInt() const;
    //PREPARE_TYPE(math::rect);

    // it will free the memory and erase all info about node
    void Clear();

    // it will give the size we needed for serialization with type size
    uint32_t RequiredSize();

    template <typename T>
    void Init(const T &param, uint32_t dataSize, VariantType paramType);

    uint8_t *data = 0;
    uint32_t size = 0;
    VariantType type = VariantType::NONE;

    ~Variant() {
        Clear();
    }
};

class VariantList {
public:
    Variant &operator[](int idx) {
        return variants[idx];
    }

    // from variantlist to memory
    uint8_t *SerializeToMem(uint32_t *outSize);
    // from memory to variantlist (initialization basically)
    void SerializeFromMem(uint8_t *data, uint32_t dataSize);

private:
    Variant variants[VARIANT_COUNT];
};