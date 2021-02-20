//
// Created on February 12th 2021 by loanselot1.
//
// Purpose: Main window hanlder of the SDK, this class allows us to switch
//          between different window libraries and handles callbacks.
//

#pragma once

#include <functional>

enum eWindowFlags {
    NONE,
    FULLSCREEN = 1 << 0,
    VSYNC = 1 << 1,
};

class Window {
public:
    Window(uint32_t width, uint32_t height, const char *title, eWindowFlags flags = NONE);
    ~Window();

    void Poll();

    bool ShouldClose() const;

    inline uint32_t Width() const {
        return m_width;
    }

    inline uint32_t Height() const {
        return m_height;
    }

    inline GLFWwindow *GetHandle() const {
        return m_handle;
    }

    static void ResizeWindow(GLFWwindow *handle, int width, int height);
    static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void MouseKeyCallback(GLFWwindow *window, int button, int action, int mods);

private:
    GLFWwindow *m_handle;
    uint32_t m_width, m_height = 0;
};