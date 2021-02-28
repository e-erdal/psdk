//
// Created on February 12th 2021 by loanselot1.
//
// Purpose: Helper functions to read and write memory cleaner.
//          This is actually implemented by ness back in 2019?
//

#pragma once

#include <cstdint>
#include <cstring>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#define MALLOC(type, ...) (type *)(malloc(sizeof(type) __VA_ARGS__))

namespace memory {
    // v2
    template <typename T>
    T Get(uint8_t *mem, uintptr_t &cur) {
        auto data = *(T *)(mem + cur);
        cur += sizeof(T);
        return data;
    }

    static std::string GetString16(uint8_t *&data, std::string *str) {
        str->assign((const char *)(data + 2), *(uint16_t *)data);
        data += 2 + str->length();
    }

    // WARNING: Unstable as fuck.
    template <typename T>
    void Append(T *val, uint8_t *mem, uint32_t &currentSize) {
        uint8_t *newMem = (uint8_t *)malloc(currentSize + sizeof(val)); // allocate memory we need
        memset(newMem, 0, currentSize + sizeof(val));                   // set it to zero

        memcpy(newMem, mem, currentSize);               // copy old memory first
        memcpy(newMem + currentSize, val, sizeof(val)); // now append the memory
        currentSize += sizeof(val);                     // memory data is now changed

        free(mem);    // clean up old one
        mem = newMem; // this is now new memory
    }

    // v1
    // from data to value
    template <typename T>
    static void Serialize(uint8_t *&data, T *val) {
        memcpy(val, data, sizeof(T));
        data += sizeof(T);
    }

    // from data to value with size
    template <typename T>
    static void Serialize(uint8_t *&data, T *val, uint32_t size) {
        memcpy(val, data, size);
        data += size;
    }

    // from data to vector
    template <typename T>
    static void SerializeIntoVector(T data, std::vector<uint8_t> &binary, uint32_t size_ = 0) {
        uint32_t size = (size_ > 0) ? size_ : sizeof(T);
        binary.insert(binary.end(), (uint8_t *)&data, (uint8_t *)&data + size);
    }

    // from data pointer to vector
    template <typename T>
    static void SerializeIntoVector(T *data, std::vector<uint8_t> &binary, uint32_t size_ = 0) {
        uint32_t size = (size_ > 0) ? size_ : sizeof(T);
        binary.insert(binary.end(), (uint8_t *)data, (uint8_t *)data + size);
    }

    // from string to vector
    static void SerializeStr8IntoVector(std::string data, std::vector<uint8_t> &binary, bool c = false) {
        uint8_t len = (c) ? (uint8_t)strlen(data.c_str()) : (uint8_t)data.length();
        binary.insert(binary.end(), (uint8_t *)&len, (uint8_t *)&len + 1);
        binary.insert(binary.end(), (uint8_t *)data.data(), (uint8_t *)data.data() + len);
    }

    static void SerializeStr16IntoVector(std::string data, std::vector<uint8_t> &binary, bool c = false) {
        uint16_t len = (c) ? (uint16_t)strlen(data.c_str()) : (uint16_t)data.length();
        binary.insert(binary.end(), (uint8_t *)&len, (uint8_t *)&len + 2);
        binary.insert(binary.end(), (uint8_t *)data.data(), (uint8_t *)data.data() + len);
    }

    // from vector to string
    static void SerializeStr8FromVector(std::string &data, std::vector<uint8_t> &binary) {
        uint8_t len = (uint8_t)data.length();
        binary.insert(binary.end(), (uint8_t *)&len, (uint8_t *)&len + 1);
        binary.insert(binary.end(), (uint8_t *)data.data(), (uint8_t *)data.data() + len);
    }

    // from data to string with pos + 4
    static void SerializeStr32(uint8_t *&data, std::string *str) {
        str->assign((const char *)(data + 4), *(uint32_t *)data);
        data += 4 + str->length();
    }

    // from data to string with pos + 2
    static void SerializeStr16(uint8_t *&data, std::string *str) {
        str->assign((const char *)(data + 2), *(uint16_t *)data);
        data += 2 + str->length();
    }

    // from data to string with pos ++
    static void SerializeStr8(uint8_t *&data, std::string *str) {
        str->assign((const char *)(data + 1), *(uint8_t *)data);
        data += 1 + str->length();
    }

    static void xorm(const std::string &key, uint8_t *data, int data_len) {
        for (int i = 0; i < data_len; i++) data[i] ^= key[i % key.length()];
    }

    static uint32_t crc16(uint8_t *str, int len) {
        if (!str)
            return 0;

        unsigned char *n = (unsigned char *)str;
        uint32_t acc = 0x55555555;

        if (len == 0) {
            while (*n) acc = (acc >> 27) + (acc << 5) + *n++;
        } else {
            for (int i = 0; i < len; i++) { acc = (acc >> 27) + (acc << 5) + *n++; }
        }
        return acc;
    }

} // namespace memory