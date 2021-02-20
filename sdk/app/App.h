//
// Created on February 13th 2021 by loanselot1.
//
// Purpose: Entrypoint of everything about SDK.
//

#pragma once

#include "pch.h"

#include "graphics/ShaderManager.h"
#include "graphics/camera/Camera.h"

#include "manager/InputManager.h"
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

    void Close();

public:
    static App *Get() {
        return g_instance;
    }

    Window *GetWindow() {
        return m_window;
    }

    ShaderManager *GetShaderManager() {
        return m_shaderMan;
    }

    Camera *GetCamera() {
        return m_camera;
    }

    InputManager *GetInputManager() {
        return m_inputMan;
    }

private:
    void Run();

private:
    Window *m_window;
    ShaderManager *m_shaderMan;
    Camera *m_camera;
    InputManager *m_inputMan;

    float m_lastDelta = 0.f;

private:
    static App *g_instance;
    friend ENTRY_POINT;
};

extern Window *GetWindow();
extern ShaderManager *GetShaderManager();
extern Camera *GetCamera();
extern InputManager *GetInputManager();