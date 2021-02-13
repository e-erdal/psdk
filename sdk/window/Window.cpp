#include "Window.h"

#include "Platform.h"
#include "graphics/RendererAPI.h"

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
    // tell glfw that we are going to use raw OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // this is what sdk's gl loader supports
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
#else
    // tell glfw that we are going to use abstraction lib (BGFX), so not really need to select api
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
#endif
#elif PLATFORM_ANDROID
    // tell glfw that we are going to use raw OpenGL ES
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2); // can we handle ES 3? I have no idea, are they that different doe
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwMakeContextCurrent(m_handle);
#endif

    m_handle = glfwCreateWindow(width, height, title, monitor, nullptr);
    if (!m_handle) {
        LOG_ERROR("Failed to create GLFW window!");
        return;
    }

    glfwMakeContextCurrent(m_handle);

    if (flags & VSYNC)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);

    DEBUG_LOG_INFO("Successfully created window. (w: %d, h: %d)", width, height);
    LOG_INFO("View (%d, %d)", width, height);
    glfwSetWindowUserPointer(m_handle, this);
    glfwSetWindowSizeCallback(m_handle, &Window::ResizeWindow);
    glfwSetKeyCallback(m_handle, &Window::KeyCallback);
    glfwSetMouseButtonCallback(m_handle, &Window::MouseKeyCallback);

    // DONT DO THIS DONT DO THIS DONT DO THIS DONT DO THIS DONT DO THIS DONT DO THIS
    // this class is not even constructed yet and requiring a valid object to initliaze? dumb
    // if (!RendererAPI::Initialize(this)) {
    //     LOG_ERROR("Something incredibly bad happen! We can't initialize renderer api?");
    //     return;
    // }
}

Window::~Window() {
    glfwDestroyWindow(m_handle);
    glfwTerminate();
}

void Window::Poll() {
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

    RendererAPI::ResetView(width, height);
}

void Window::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
}

void Window::MouseKeyCallback(GLFWwindow *window, int button, int action, int mods) {
}

void Window::SetDrawCallback(DrawCallback_t callback) {
    m_drawCallback = callback;
}

void Window::SetDrawInitCallback(DrawInitCallback_t callback) {
    m_drawInitCallback = callback;
}