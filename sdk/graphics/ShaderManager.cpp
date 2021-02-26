#include "ShaderManager.h"

#include "utils/Memory.h"

#include "filesystem/FileSystem.h"

void ShaderManager::Add(const std::string &key, bgfx::RendererType::Enum renderer, eShaderType type, uint8_t *data, uint32_t dataLen) {
    m_shaders.push_back(Shader{ key, renderer, type, data, dataLen });
}

bgfx::ShaderHandle ShaderManager::LoadShader(const std::string &key, const eShaderType shaderType) {
    Shader *p_shader = nullptr;

    for (auto &shader : m_shaders) {
        if (shader.name == key && shader.type == shaderType && shader.renderer == bgfx::getRendererType()) {
            p_shader = &shader;
            break;
        }
    }

    if (p_shader == nullptr)
        return BGFX_INVALID_HANDLE;

    const auto *buffer = bgfx::copy(p_shader->code, p_shader->code_len);
    const auto handle = bgfx::createShader(buffer);

    return handle;
}

bgfx::ProgramHandle ShaderManager::LoadProgram(const std::string &key) {
    if (m_programs.find(key) != m_programs.end())
        return m_programs[key];

    const auto vsh = this->LoadShader(key, eShaderType::Vertex);
    const auto fsh = this->LoadShader(key, eShaderType::Fragment);

    const auto handle = bgfx::createProgram(vsh, fsh, true);

    m_programs[key] = handle;

    return handle;
}

#if 0
#include "s/fs_default.d3d11.h"
#include "s/fs_default.d3d12.h"
#include "s/fs_default.d3d9.h"
#include "s/fs_default.glsl.h"
#include "s/fs_default.metal.h"
#include "s/fs_default.vulkan.h"
#include "s/vs_default.d3d11.h"
#include "s/vs_default.d3d12.h"
#include "s/vs_default.d3d9.h"
#include "s/vs_default.glsl.h"
#include "s/vs_default.metal.h"
#include "s/vs_default.vulkan.h"
#endif

void ShaderManager::Add(const char *path, const char *name) {
    uint32_t readSize = 0;
    uint8_t *data = FileSystem::ReadBinaryFile(path, &readSize);
    uint8_t *ptr = data;

    for (size_t j = 0; j < 12; j++) {
        Shader i{};
        i.name = name;
        memory::Serialize(data, &i.type, 1);
        memory::Serialize(data, &i.renderer, 1);
        memory::Serialize(data, &i.code_len);
        i.code = (uint8_t *)malloc(i.code_len);
        memory::Serialize(data, i.code, i.code_len);
        m_shaders.push_back(i);
    }

    data = ptr;
    free(data);
}

void ShaderManager::InitializeSpriteShaders() {
#if 1
    Add("data/shaders/default.shader", "Default");
#else

    // clang-format off
    Add(SHADER_NAME, bgfx::RendererType::Direct3D9,   eShaderType::Fragment,  (uint8_t *)fs_gaussian_blur_hz_d3d9,      sizeof(fs_gaussian_blur_hz_d3d9));
    Add(SHADER_NAME, bgfx::RendererType::Direct3D11,  eShaderType::Fragment,  (uint8_t *)fs_gaussian_blur_hz_d3d11,     sizeof(fs_gaussian_blur_hz_d3d11));
    Add(SHADER_NAME, bgfx::RendererType::Direct3D12,  eShaderType::Fragment,  (uint8_t *)fs_gaussian_blur_hz_d3d12,     sizeof(fs_gaussian_blur_hz_d3d12));
    Add(SHADER_NAME, bgfx::RendererType::OpenGL,      eShaderType::Fragment,  (uint8_t *)fs_gaussian_blur_hz_glsl,      sizeof(fs_gaussian_blur_hz_glsl));
    Add(SHADER_NAME, bgfx::RendererType::Metal,       eShaderType::Fragment,  (uint8_t *)fs_gaussian_blur_hz_metal,     sizeof(fs_gaussian_blur_hz_metal));
    Add(SHADER_NAME, bgfx::RendererType::Vulkan,      eShaderType::Fragment,  (uint8_t *)fs_gaussian_blur_hz_vulkan,    sizeof(fs_gaussian_blur_hz_vulkan));

    Add(SHADER_NAME, bgfx::RendererType::Direct3D9,   eShaderType::Vertex,    (uint8_t *)vs_gaussian_blur_d3d9,      sizeof(vs_gaussian_blur_d3d9));
    Add(SHADER_NAME, bgfx::RendererType::Direct3D11,  eShaderType::Vertex,    (uint8_t *)vs_gaussian_blur_d3d11,     sizeof(vs_gaussian_blur_d3d11));
    Add(SHADER_NAME, bgfx::RendererType::Direct3D12,  eShaderType::Vertex,    (uint8_t *)vs_gaussian_blur_d3d12,     sizeof(vs_gaussian_blur_d3d12));
    Add(SHADER_NAME, bgfx::RendererType::OpenGL,      eShaderType::Vertex,    (uint8_t *)vs_gaussian_blur_glsl,      sizeof(vs_gaussian_blur_glsl));
    Add(SHADER_NAME, bgfx::RendererType::Metal,       eShaderType::Vertex,    (uint8_t *)vs_gaussian_blur_metal,     sizeof(vs_gaussian_blur_metal));
    Add(SHADER_NAME, bgfx::RendererType::Vulkan,      eShaderType::Vertex,    (uint8_t *)vs_gaussian_blur_vulkan,    sizeof(vs_gaussian_blur_vulkan));

    std::vector<uint8_t> v;
    for (auto &&i : m_shaders) {
        memory::SerializeIntoVector(i.type, v, 1);
        memory::SerializeIntoVector(i.renderer, v, 1);
        memory::SerializeIntoVector(i.code_len, v);
        memory::SerializeIntoVector(i.code, v, i.code_len);
    }

    FileSystem::WriteBinaryFile(SHADER_NAME "-HZ.shader", v.data(), v.size());
    std::vector<uint8_t>().swap(v);
#endif
}