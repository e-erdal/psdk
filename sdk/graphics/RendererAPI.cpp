#include "RendererAPI.h"

#include "app/App.h"

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
    bgfx::PlatformData platformData;
#if PLATFORM_WINDOWS
    platformData.nwh = glfwGetWin32Window(GetWindow()->GetHandle());
#elif PLATFORM_ANDROID
    platformData.nwh = glfwGetAndroidApp(m_handle)->window;
    platformData.ndt = 0;
    eglDestroySurface(eglGetDisplay(EGL_DEFAULT_DISPLAY), glfwGetEGLSurface(m_handle));
#endif
    bgfx::Init init;
    init.debug = false;
    init.type = bgfx::RendererType::Count;
    init.platformData = platformData;
    init.resolution.width = GetWindow()->Width();
    init.resolution.height = GetWindow()->Height();
    init.resolution.reset = BGFX_RESET_NONE;
    init.limits.transientVbSize = g_MaxVBCount;

    if (!bgfx::init(init)) {
        LOG_ERROR("Failed to initialize BGFX!");
        return;
    }

    DEBUG_LOG_INFO("Successfully initialized BGFX.");
    Clear(0, 0, 0, 255);
    bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);
}

void RendererAPI::Clear(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, MAKE_RGBA(r, g, b, a), 1.0f, 0);
}

void RendererAPI::ResetView(int32_t width, int32_t height) {
    bgfx::reset(GetWindow()->Width(), GetWindow()->Height(), BGFX_RESET_NONE);
    bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);
}