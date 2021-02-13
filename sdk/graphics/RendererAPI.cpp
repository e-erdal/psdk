#include "RendererAPI.h"

#include "window/Window.h"

bool RendererAPI::Initialize(Window *wapi) {
#if CURRENT_API_OPENGL
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LOG_ERROR("Could not load OpenGL for api context! RAPI failed.");
        return false;
    }
#endif

    InitializeSettings();
    return true;
}

void RendererAPI::InitializeSettings() {
#if CURRENT_API_OPENGL
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
#endif
}

void RendererAPI::DrawIndexed(uint32_t count) {
#if CURRENT_API_OPENGL
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
#endif
}

void RendererAPI::Clear(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
#if CURRENT_API_OPENGL
    glClearColor((float)r / 255.f, (float)g / 255.f, (float)g / 255.f, (float)a / 255.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#endif
}

void RendererAPI::ResetView(int32_t width, int32_t height) {
#if CURRENT_API_OPENGL
    glViewport(0, 0, width, height);
#endif
}