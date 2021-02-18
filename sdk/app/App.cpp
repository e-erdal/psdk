#include "App.h"

#include "graphics/RendererAPI.h"

App *App::g_instance = 0;

App::App(const AppInfo &info) {
    g_instance = this;

    m_window = new Window(info.windowRes.x, info.windowRes.y, info.title, info.windowFlags);
    m_shaderMan = new ShaderManager();
    m_shaderMan->InitializeSpriteShaders();

    RendererAPI::Initialize(m_window);
}

App::~App() {
    // deinit RAPI
}

void App::Run() {
    while (!m_window->ShouldClose()) {
        bgfx::touch(0);
        m_window->Poll();
        bgfx::frame();
    }
}

// externals //////////////////
Window *GetWindow() {
    return App::Get()->GetWindow();
}

ShaderManager *GetShaderManager() {
    return App::Get()->GetShaderManager();
}