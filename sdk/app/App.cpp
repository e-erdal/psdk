#include "App.h"

#include "graphics/RendererAPI.h"

App *App::g_instance = 0;

App::App(const AppInfo &info) {
    g_instance = this;

    m_window = new Window(info.windowRes.x, info.windowRes.y, info.title, info.windowFlags);

    RendererAPI::Initialize(m_window);
}

App::~App() {
    // deinit RAPI
}

void App::Run() {
    while (!m_window->ShouldClose()) {
        RendererAPI::Clear(0, 0, 0, 255);
        m_window->Poll();
    }
}