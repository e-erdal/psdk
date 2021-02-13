//
// Created on February 13th 2021 by loanselot1.
//
// Purpose: Cross platform file I/O utility.
//

#pragma once

#include "pch.h"

namespace FileSystem {
    constexpr std::string_view GetFileName(std::string_view path) noexcept {
        for (auto i = path.size(); i > 0; --i)
            if (path[i] == '/' || path[i] == '\\')
                return std::string_view(&path[0] + (i + 1));

        return path; // Not found...
    }

    constexpr bool HasExtension(std::string_view path, std::string_view ext) noexcept {
        if (path.length() < ext.length())
            return false;

        return (0 == path.compare(path.length() - ext.length(), ext.length(), ext));
    }

    void MkDir(const std::string &path);
    std::string JoinPath(const std::string &p1, const std::string &p2);
    bool Exists(const std::string &path);
    bool IsDirectory(const std::string &path);
    std::vector<std::string> ReadDirectory(const std::string &path, bool pRecursive = false);
    std::string ResolveFullPath(const std::string &path);

    uint8_t *ReadBinaryFile(const char *path, uint32_t *size);
    std::string ReadTextFile(const char *path);
    void WriteBinaryFile(const std::string &path, uint8_t *data, uint32_t size);

    void Touch(const std::string &path);
    void Delete(const std::string &path);
} // namespace FileSystem