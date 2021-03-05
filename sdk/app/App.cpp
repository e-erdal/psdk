#include "App.h"

#include "entity/EntityUtils.h"

#include "graphics/RenderBatcher.h"
#include "graphics/RendererAPI.h"

#include "manager/input/Helpers.h"

App *App::g_instance = 0;

void App::Setup(const AppInfo &info) {
    g_instance = this;

    logger::Clear();
    m_window = new Window(info.windowRes.x, info.windowRes.y, info.title, info.windowFlags);
    m_shaderMan = new ShaderManager();
    m_shaderMan->InitializeSpriteShaders();
    m_inputMan = new (InputManager);

    RendererAPI::Initialize(m_window);
    RenderBatcher::Initialize();

    m_camera = new Camera(0, 0, m_window->Width(), m_window->Height());

    m_entityRoot = new Entity();
}

App::~App() {
    // deinit RAPI
}

void App::Run() {
    while (!m_window->ShouldClose()) {
        RendererAPI::NewFrame();
        m_camera->CalculateTransformation();

        RenderBatcher::NewFrame();

        RenderAllEntities(GetEntityRoot());

        RenderBatcher::EndFrame();

        RendererAPI::Draw();

        Update();
        UpdateAllEntities(GetEntityRoot(), 0.f);

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

Entity *GetEntityRoot() {
    return App::Get()->GetEntityRoot();
}