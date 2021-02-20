#include "App.h"

#include "graphics/RenderBatcher.h"
#include "graphics/RendererAPI.h"

App *App::g_instance = 0;

App::App(const AppInfo &info) {
    g_instance = this;

    m_window = new Window(info.windowRes.x, info.windowRes.y, info.title, info.windowFlags);
    m_shaderMan = new ShaderManager();
    m_shaderMan->InitializeSpriteShaders();
    m_inputMan = new (InputManager);

    RendererAPI::Initialize(m_window);
    RenderBatcher::Initialize();

    m_camera = new Camera(0, 0, m_window->Width(), m_window->Height());
}

App::~App() {
    // deinit RAPI
}

#include <glm/gtx/transform.hpp>

void DrawChunk(size_t xx, size_t yy) {
    for (size_t y = yy; y < yy + 50; y++)
        for (size_t x = xx; x < xx + 50; x++) {
            glm::mat4 transform = glm::translate(glm::mat4(1.f), { (float)(x * 32), (float)(y * 32), 1.f }) * glm::scale(glm::mat4(1.f), { 31.f, 31.f, 1.f });
            RenderBatcher::DrawRectangle(transform, { 1, (float)x / 255.f, (float)y / 255.f, 1 });
        }
}

void App::Run() {
    while (!m_window->ShouldClose()) {
        m_window->Poll();

        bgfx::touch(0);
        m_camera->CalculateTransformation();

        RenderBatcher::NewFrame();
        for (size_t y = 0; y < 2; y++)
            for (size_t x = 0; x < 2; x++) {
                DrawChunk(x * 50, y * 50);
                RenderBatcher::ResetBatch();
            }

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

Camera *GetCamera() {
    return App::Get()->GetCamera();
}

InputManager *GetInputManager() {
    return App::Get()->GetInputManager();
}