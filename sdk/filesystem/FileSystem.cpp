#include "FileSystem.h"

#include <filesystem>

#ifdef _WIN32
#include <Windows.h>
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_LINUX)
#include <sys/stat.h>

#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>

#include <cstdlib>
#endif

std::string FileSystem::JoinPath(const std::string &p1, const std::string &p2) {
    if (p1.length() <= 0)
        return p2.data();

    if (p2.length() <= 0)
        return p1.data();

    if (p1[p1.length() - 1] == '/' || p1[p1.length() - 1] == '\\')
        return std::string(p1.data()) + p2.data();

    return std::string(p1) + "/" + p2.data();
}

bool FileSystem::Exists(const std::string &pPath) {
#if PLATFORM_WINDOWS
    const auto dir_type = GetFileAttributesA(pPath.data());

    return dir_type != INVALID_FILE_ATTRIBUTES;
#elif PLATFORM_LINUX || PLATFORM_ANDROID
    return (access(pPath.data(), F_OK) != -1);
#else
#error "Platform not implemented!"
#endif
    return false;
}

bool FileSystem::IsDirectory(const std::string &pPath) {
    if (!Exists(pPath))
        return false;

#if PLATFORM_WINDOWS
    return GetFileAttributes(pPath.data()) & FILE_ATTRIBUTE_DIRECTORY;
#elif PLATFORM_LINUX || PLATFORM_LINUX
    struct stat st;
    stat(pPath.data(), &st);
    return S_ISDIR(st.st_mode);
#else
#error "Platform not implemented!"
#endif
    return false;
}

std::string FileSystem::ResolveFullPath(const std::string &pPath) {
#if PLATFORM_WINDOWS
    char buffer[4096];
    if (IS_ERROR(GetFullPathNameA(pPath.data(), 4096, buffer, nullptr)))
        return "";

    return buffer;
#elif PLATFORM_LINUX || PLATFORM_LINUX
    char buffer[PATH_MAX + 1];

    realpath(pPath.data(), buffer);

    return std::string(buffer);
#else
#error "Platform not implemented!"
#endif
    return "";
}

uint8_t *FileSystem::ReadBinaryFile(const char *path, uint32_t *size) {
#if PLATFORM_LINUX || PLATFORM_LINUX
    auto fp = open(path.data(), O_WRONLY | O_CREAT, umask(0755));
    if (fp < 0)
        LOG_ERROR("Failed to open %s", path.data());

    write(fp, data, size);

    close(fp);
#elif PLATFORM_WINDOWS
    FILE *fp = fopen(path, "rb");
    if (!fp) {
        LOG_ERROR("Failed to open '%s'.", path);
        return nullptr;
    }

    fseek(fp, 0, SEEK_END);
    const uint32_t fileSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    if (fileSize <= 0)
        return nullptr;

    uint8_t *data = (uint8_t *)malloc(fileSize);

    if (!data) {
        LOG_ERROR("OUT OF MEMORY WHILE READING %s", path);
        fclose(fp);
        return nullptr;
    }

    fread(data, fileSize, 1, fp);
    fclose(fp);

    *size = fileSize;
    return data;
#endif
}

std::string FileSystem::ReadTextFile(const char *path) {
    uint32_t len = 0;
    uint8_t *data = ReadBinaryFile(path, &len);
    std::string ret((const char *)data, len);
    free(data);
    return ret;
}

void FileSystem::WriteBinaryFile(const std::string &path, uint8_t *data, uint32_t size) {
#if PLATFORM_LINUX || PLATFORM_LINUX
    auto fp = open(path.data(), O_WRONLY | O_CREAT, umask(0755));
    if (fp < 0)
        LOG_ERROR("Failed to open %s", path.data());

    write(fp, data, size);

    close(fp);
#else
    FILE *fp = fopen(path.data(), "wb");
    if (!fp)
        LOG_ERROR("Failed to open '%s'", path.data());

    if (data)
        fwrite(data, size, 1, fp); // maybe we want to touch the file

    fclose(fp);
#endif

#if PLATFORM_LINUX || PLATFORM_LINUX
    chmod(path.data(),
        umask(0755)); // set the correct permissions cause it's wrong
#endif
}

void FileSystem::MkDir(const std::string &pPath) {
#ifdef _WIN32
    CreateDirectory(pPath.data(), NULL);
#elif PLATFORM_LINUX || PLATFORM_LINUX
    if (mkdir(pPath.data(), umask(0755)))
        LOG_ERROR("Failed to create Directory! %s", pPath.data());

    chmod(pPath.data(), umask(0755)); // set the correct permissions cause
                                      // it's wrong for some reason
#else
#error "Platform not implemented!"
#endif
}

void FileSystem::Touch(const std::string &pPath) {
    WriteBinaryFile(pPath, nullptr, 0);
}

void FileSystem::Delete(const std::string &pPath) {
    remove(pPath.data());
}