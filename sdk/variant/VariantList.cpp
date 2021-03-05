#include "VariantList.h"

#include "entity/Entity.h"
#include "entity/component/EntityComponent.h"

#include "utils/Memory.h"

template <typename T>
void Variant::Init(const T &param, uint32_t dataSize, VariantType paramType) {
    data = (uint8_t *)realloc(data, dataSize);
    memcpy(data, &param, dataSize);

    size = dataSize;
    type = paramType;
}

Variant &Variant::operator=(const float &param) {
    Init(param, sizeof(param), VariantType::FLOAT);
    return *this;
}

Variant &Variant::operator=(const std::string &param) {
    data = (uint8_t *)realloc(data, param.length());
    memcpy(data, param.c_str(), param.length());

    size = param.length();
    type = VariantType::STRING;
    return *this;
}

Variant &Variant::operator=(const glm::vec2 &param) {
    Init(param, sizeof(param), VariantType::VECTOR2);
    return *this;
}

Variant &Variant::operator=(const glm::vec3 &param) {
    Init(param, sizeof(param), VariantType::VECTOR3);
    return *this;
}

Variant &Variant::operator=(const uint32_t &param) {
    Init(param, sizeof(param), VariantType::UINT32);
    return *this;
}

Variant &Variant::operator=(const Entity *param) {
    Init(param, sizeof(param), VariantType::ENTITY);
    return *this;
}

Variant &Variant::operator=(const EntityComponent *param) {
    Init(param, sizeof(param), VariantType::COMPONENT);
    return *this;
}

Variant &Variant::operator=(const int32_t &param) {
    Init(param, sizeof(param), VariantType::INT32);
    return *this;
}

Variant &Variant::operator=(const glm::mat4 &param) {
    Init(param, sizeof(param), VariantType::MAT4X4);
    return *this;
}

//////////////////////////////////////////////////////////////////////

float &Variant::GetFloat() {
    if (type == VariantType::NONE)
        Set(0.f);

    return *(float *)data;
}

std::string Variant::GetString() {
    if (type == VariantType::NONE)
        Set("");

    return std::string((const char *)data, size);
}

glm::vec2 &Variant::GetVec2() {
    if (type == VariantType::NONE)
        Set(glm::vec2{ 0.f, 0.f });

    return *(glm::vec2 *)data;
}

glm::vec3 &Variant::GetVec3() {
    if (type == VariantType::NONE)
        Set(glm::vec3{ 0.f, 0.f, 0.f });

    return *(glm::vec3 *)data;
}

Entity *Variant::GetEntity() {
    if (type == VariantType::NONE)
        return 0;

    return ((Entity *)data);
}

EntityComponent *Variant::GetComponent() {
    if (type == VariantType::NONE)
        return 0;

    return ((EntityComponent *)data);
}

uint32_t &Variant::GetUInt() {
    if (type == VariantType::NONE)
        Set(0u);

    return *(uint32_t *)data;
}

int32_t &Variant::GetInt() {
    if (type == VariantType::NONE)
        Set(0i32);

    return *(int32_t *)data;
}

glm::mat4 &Variant::GetMat4() {
    if (type == VariantType::NONE)
        Set(glm::mat4{ 0.f });

    return *(glm::mat4 *)data;
}

//////////////////////////////////////////////////////////////////////

void Variant::Clear() {
    if (data)
        free(data);

    size = 0;
    type = VariantType::NONE;
}

uint32_t Variant::RequiredSize() {
    uint32_t ret = 0;
    switch (type) {
        case VariantType::UINT32:
        case VariantType::INT32:
            ret += 2;
            ret += 4;
            break;

        case VariantType::FLOAT:
            ret += 2;
            ret += 4;
            break;

        case VariantType::STRING:
            ret += 2;
            ret += 4; // data size
            ret += size;
            break;

        default: break;
    }

    return ret;
}

uint8_t *VariantList::SerializeToMem(uint32_t *outSize) {
    uint32_t requested_size = 0;
    uint8_t used_variants = 0;

    for (size_t i = 0; i < VARIANT_COUNT; i++) {
        auto vsize = variants[i].RequiredSize();
        requested_size += vsize;
        if (vsize)
            used_variants++;
    }

    uint8_t *ret = (uint8_t *)malloc(requested_size + 1);
    uint8_t *ptr = ret;
    memcpy(ret++, &used_variants, 1);

    for (size_t i = 0; i < VARIANT_COUNT; i++) {
        switch (variants[i].type) {
            case VariantType::NONE: break;
            case VariantType::STRING:
                memcpy(ret++, &i, 1);
                memcpy(ret++, &variants[i].type, 1);
                memcpy(ret, &variants[i].size, 4);
                ret += 4;
                memcpy(ret, variants[i].data, variants[i].size);
                ret += variants[i].size;
                break;

            default:
                memcpy(ret++, &i, 1);
                memcpy(ret++, &variants[i].type, 1);
                memcpy(ret, variants[i].data, variants[i].size);
                ret += variants[i].size;
                break;
        }
    }

    ret = ptr;
    *outSize = requested_size + 1;
    return ret;
}

void VariantList::SerializeFromMem(uint8_t *data, uint32_t dataSize) {
    uint8_t *data_ptr = data;

    uint8_t varCount = 0;
    memory::Serialize(data, &varCount);
    for (size_t i = 0; i < varCount; i++) {
        uint8_t idx = 0;
        memory::Serialize(data, &idx);
        VariantType type = VariantType::NONE;
        memory::Serialize(data, &type);
        switch (type) {
            case VariantType::FLOAT: {
                float var = 0.f;
                memory::Serialize(data, &var);
                variants[idx] = var;
                break;
            }

            case VariantType::STRING: {
                std::string var = "";
                memory::SerializeStr32(data, &var);
                variants[idx] = var;
                break;
            }

            case VariantType::VECTOR2: {
                glm::vec2 var{};
                memory::Serialize(data, &var);
                variants[idx] = var;
                break;
            }

            case VariantType::VECTOR3: {
                glm::vec3 var{};
                memory::Serialize(data, &var);
                variants[idx] = var;
                break;
            }

            case VariantType::UINT32: {
                uint32_t var = 0;
                memory::Serialize(data, &var);
                variants[idx] = var;
                break;
            }

                // case VariantType::RECT: {
                //     math::rect var{};
                //     memory::Serialize(data, &var);
                //     variants[idx] = var;
                //     break;
                // }

            case VariantType::INT32: {
                int32_t var = 0;
                memory::Serialize(data, &var);
                variants[idx] = var;
                break;
            }

            case VariantType::MAT4X4: {
                glm::mat4 var{};
                memory::Serialize(data, &var);
                variants[idx] = var;
                break;
            }

            default: break;
        }
    }

    data = data_ptr;
}