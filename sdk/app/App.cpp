#include "App.h"

#include "graphics/RenderBatcher.h"
#include "graphics/RendererAPI.h"

#include "manager/input/Helpers.h"

App *App::g_instance = 0;

App::App(const AppInfo &info) {
    g_instance = this;

    logger::Clear();
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

std::vector<glm::vec2> rects;

void App::Run() {
    while (!m_window->ShouldClose()) {
        RendererAPI::NewFrame();
        m_camera->CalculateTransformation();

        RenderBatcher::NewFrame();
        // for (size_t y = 0; y < 2; y++)
        //     for (size_t x = 0; x < 2; x++) {
        //         DrawChunk(x * 50, y * 50);
        //         RenderBatcher::ResetBatch();
        //     }
        for (auto &&i : rects) {
            glm::mat4 transform = glm::translate(glm::mat4(1.f), { i.x, i.y, 1.f }) * glm::scale(glm::mat4(1.f), { 31.f, 31.f, 1.f });
            RenderBatcher::DrawRectangle(transform, { 1, i.x / 255.f, i.y / 255.f, 1 });
        }

        glm::mat4 transform =
            glm::translate(glm::mat4(1.f), { m_inputMan->GetMousePos().x - 16, m_inputMan->GetMousePos().y - 16, 1.f }) * glm::scale(glm::mat4(1.f), { 31.f, 31.f, 1.f });
        RenderBatcher::DrawRectangle(transform, { 1, m_inputMan->GetMousePos().x / 255.f, m_inputMan->GetMousePos().y / 255.f, 1 });

        RenderBatcher::EndFrame();

        RendererAPI::Draw();

        if (m_inputMan->IsMouseClicked(INPUT_MOUSE_STATE_LEFT)) {
            rects.push_back({ m_inputMan->GetMousePos().x - 16, m_inputMan->GetMousePos().y - 16 });
        }

        m_window->Poll();
        m_inputMan->Update(); // this shit has to stay on bottom, no matter what
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