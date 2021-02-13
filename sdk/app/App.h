//
// Created on February 13th 2021 by loanselot1.
//
// Purpose: Entrypoint of everything about SDK.
//

#pragma once

#include "pch.h"

#include "window/Window.h"

struct AppInfo {
    std::string appName;
    int verMaj;
    int verMin;
    int verBuild;

    const char *title;
    glm::ivec2 windowRes;
    eWindowFlags windowFlags;
};

class App {
public:
    App(const AppInfo &info);
    virtual ~App();

    static App *Get() {
        return g_instance;
    }

    void Close();

private:
    void Run();

private:
    Window *m_window;

    float m_lastDelta = 0.f;

private:
    static App *g_instance;
    friend ENTRY_POINT;
};