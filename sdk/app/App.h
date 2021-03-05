//
// Created on February 13th 2021 by loanselot1.
//
// Purpose: Entrypoint of everything about SDK.
//

#pragma once

#include "pch.h"

#include "entity/Entity.h"
#include "entity/EntityUtils.h"

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
    App(){};
    virtual ~App();

    void Setup(const AppInfo &info);

    virtual bool Init() = 0;
    virtual void Kill() = 0;
    virtual void Update() = 0;

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

    Entity *GetEntityRoot() {
        return m_entityRoot;
    }

private:
    void Run();

private:
    Window *m_window;
    ShaderManager *m_shaderMan;
    Camera *m_camera;
    InputManager *m_inputMan;

    Entity *m_entityRoot = 0;

    float m_lastDelta = 0.f;

private:
    static App *g_instance;
    friend ENTRY_POINT();
};

extern Window *GetWindow();
extern ShaderManager *GetShaderManager();
extern Camera *GetCamera();
extern InputManager *GetInputManager();
extern Entity *GetEntityRoot();