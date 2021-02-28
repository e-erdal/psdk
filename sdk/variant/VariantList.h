//
// Created on February 12th 2021 by loanselot1.
//
// Purpose: Magical stuff that you can store multiple data in one param. How amazing?
//

#pragma once

#include <stdint.h>

#include <string>

#define VARIANT_COUNT 6

class Entity;
class EntityComponent;

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
    // clang-format off
    Variant() {}
    Variant(uint32_t var)               { this->operator= (var); }
	Variant(int32_t var)                { this->operator= (var); }
	Variant(float var)                  { this->operator= (var); }
	Variant(const std::string &var)     { this->operator= (var); }
	Variant(float x, float y)           { this->operator= (glm::vec2(x,y)); }
	Variant(float x, float y, float z)  { this->operator= (glm::vec3(x,y,z)); }
	Variant(const glm::vec2 &v2)        { this->operator= (v2); }
	Variant(const glm::vec3 &v3)        { this->operator= (v3); }
	Variant(Entity *entity)             { this->operator= (entity); }
	Variant(EntityComponent *component) { this->operator= (component); }
    // clang-format on

    // types
    Variant &operator=(const float &param);
    float &GetFloat() const;

    Variant &operator=(const std::string &param);
    std::string GetString() const;

    Variant &operator=(const glm::vec2 &param);
    glm::vec2 &GetVec2() const;

    Variant &operator=(const glm::vec3 &param);
    glm::vec3 &GetVec3() const;

    Variant &operator=(const uint32_t &param);
    uint32_t &GetUInt() const;

    Variant &operator=(const Entity *param);
    Entity *GetEntity() const;

    Variant &operator=(const EntityComponent *param);
    EntityComponent *GetComponent() const;

    Variant &operator=(const int32_t &param);
    int32_t &GetInt() const;

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
    // clang-format off
    VariantList() {}
    VariantList(Variant v0) {variants[0] = v0;}
	VariantList(Variant v0, Variant v1) {variants[0] = v0; variants[1] = v1;}
	VariantList(Variant v0, Variant v1, Variant v2) {variants[0] = v0; variants[1] = v1; variants[2] = v2;}
	VariantList(Variant v0, Variant v1, Variant v2, Variant v3) {variants[0] = v0; variants[1] = v1; variants[2] = v2; variants[3] = v3;}
	VariantList(Variant v0, Variant v1, Variant v2, Variant v3, Variant v4) {variants[0] = v0; variants[1] = v1; variants[2] = v2; variants[3] = v3; variants[4] = v4;}
	VariantList(Variant v0, Variant v1, Variant v2, Variant v3, Variant v4, Variant v5) {variants[0] = v0; variants[1] = v1; variants[2] = v2; variants[3] = v3; variants[4] = v4;  variants[5] = v5;}

    // clang-format on

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