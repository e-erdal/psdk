#include "Window.h"

#include "Platform.h"
#include "renderer/RendererAPI.h"

Window::Window(uint32_t width, uint32_t height, const char *title, eWindowFlags flags) : m_width(width), m_height(height) {
    if (!glfwInit()) {
        LOG_ERROR("Failed to initialize GLFW!");
        return;
    }

    GLFWmonitor *monitor = nullptr;
    if (flags & eWindowFlags::FULLSCREEN)
        monitor = glfwGetPrimaryMonitor();

#if PLATFORM_WINDOWS
#if CURRENT_API_OPENGL
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
#else
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
#endif
#elif PLATFORM_ANDROID
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwMakeContextCurrent(m_handle);
#endif
    m_handle = glfwCreateWindow(width, height, title, monitor, nullptr);
    if (!m_handle)
        LOG_ERROR("Failed to create GLFW window!");

    DEBUG_LOG_INFO("Successfully created window. (w: %d, h: %d)", width, height);
    LOG_INFO("View (%d, %d)", width, height);
    glfwSetWindowUserPointer(m_handle, this);
    glfwSetWindowSizeCallback(m_handle, &Window::ResizeWindow);
    glfwSetKeyCallback(m_handle, &Window::KeyCallback);
    glfwSetMouseButtonCallback(m_handle, &Window::MouseKeyCallback);

    bgfx::PlatformData platformData;
#if PLATFORM_WINDOWS
    platformData.nwh = glfwGetWin32Window(m_handle);
#elif PLATFORM_ANDROID
    platformData.nwh = glfwGetAndroidApp(m_handle)->window;
    platformData.ndt = 0;
    eglDestroySurface(eglGetDisplay(EGL_DEFAULT_DISPLAY), glfwGetEGLSurface(m_handle));
#endif
    bgfx::Init bgfxInit;
    bgfxInit.debug = false;
    bgfxInit.type = bgfx::RendererType::Count;
    bgfxInit.platformData = platformData;
    bgfxInit.resolution.width = m_width;
    bgfxInit.resolution.height = m_height;
    bgfxInit.resolution.reset = BGFX_RESET_NONE;
    if (!bgfx::init(bgfxInit))
        LOG_ERROR("Failed to initialize BGFX!");

    DEBUG_LOG_INFO("Successfully initialized BGFX.");
    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x000000FF, 1.0f, 0);
    bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);
}

Window::~Window() {
    bgfx::shutdown();
    glfwDestroyWindow(m_handle);
    glfwTerminate();
}

void Window::Poll() {
    DH_PROFILE_FUNCTION();
    glfwSwapBuffers(m_handle);
    glfwPollEvents();
}

bool Window::ShouldClose() const {
    return glfwWindowShouldClose(m_handle);
}

void Window::ResizeWindow(GLFWwindow *handle, int width, int height) {
    Window *ptr = (Window *)glfwGetWindowUserPointer(handle);
    ptr->m_width = (uint32_t)width;
    ptr->m_height = (uint32_t)height;

    CameraSystem::GetActiveCamera(GetActiveScene()).SetScaleCamera({ width, height });

    bgfx::reset(ptr->m_width, ptr->m_height, BGFX_RESET_NONE);
    bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);
}

void Window::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    inputpipeline::ProcessKeyboard(key, scancode, action, mods);
}

void Window::MouseKeyCallback(GLFWwindow *window, int button, int action, int mods) {
    inputpipeline::ProcessMouse(button, action, mods);
}

void Window::SetDrawCallback(DrawCallback_t callback) {
    m_drawCallback = callback;
}

void Window::SetDrawInitCallback(DrawInitCallback_t callback) {
    m_drawInitCallback = callback;
}