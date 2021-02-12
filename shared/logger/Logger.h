//
// Created on February 12th 2021 by loanselot1.
//
// Purpose: Logging handler for both console and file.
//

#pragma once

#define LOG(x, ...) logger::Logf(x "\n", ##__VA_ARGS__)

// clang-format off
#ifdef _DEBUG
#define LOG_INFO(x, ...)        logger::Logf(" ---- | INFO  | " x "\n", ##__VA_ARGS__)
#define LOG_WARN(x, ...)        logger::Logf(" ---- | WARN  | " x "\n", ##__VA_ARGS__)
#define LOG_ERROR(x, ...)       logger::Logf(" ---- | ERROR | " x "\n", ##__VA_ARGS__)
#define DEBUG_LOG_INFO(x, ...)  logger::Logf("DEBUG | INFO  | [%s:%d - '%s']: " x "\n", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define DEBUG_LOG_WARN(x, ...)  logger::Logf("DEBUG | WARN  | [%s:%d - '%s']: " x "\n", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define DEBUG_LOG_ERROR(x, ...) logger::Logf("DEBUG | ERROR | [%s:%d - '%s']: " x "\n", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
#define LOG_INFO(x, ...)        logger::Logf("INFO  | " x "\n", ##__VA_ARGS__)
#define LOG_WARN(x, ...)        logger::Logf("WARN  | " x "\n", ##__VA_ARGS__)
#define LOG_ERROR(x, ...)       logger::Logf("ERROR | " x "\n", ##__VA_ARGS__)
#define DEBUG_LOG_INFO(x, ...)  (void *)0;
#define DEBUG_LOG_WARN(x, ...)  (void *)0;
#define DEBUG_LOG_ERROR(x, ...) (void *)0;
#endif
// clang-format on

namespace logger {
    void Clear();
    void Logf(const char *output, ...);
} // namespace logger