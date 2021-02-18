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

void ShaderManager::InitializeSpriteShaders() {
#if 1
    uint32_t readSize = 0;
    uint8_t *data = FileSystem::ReadBinaryFile("data/shaders/default.shader", &readSize);
    uint8_t *ptr = data;

    m_shaders.resize(m_shaders.size() + 12);

    for (auto &&i : m_shaders) {
        i.name = "Default";
        memory::Serialize(data, &i.type, 1);
        memory::Serialize(data, &i.renderer, 1);
        memory::Serialize(data, &i.code_len);
        i.code = (uint8_t *)malloc(i.code_len);
        memory::Serialize(data, i.code, i.code_len);
    }

    data = ptr;
    free(data);

#else

    // clang-format off
    Add("Default", bgfx::RendererType::Direct3D9,   eShaderType::Fragment,  (uint8_t *)fs_default_d3d9,      sizeof(fs_default_d3d9));
    Add("Default", bgfx::RendererType::Direct3D11,  eShaderType::Fragment,  (uint8_t *)fs_default_d3d11,     sizeof(fs_default_d3d11));
    Add("Default", bgfx::RendererType::Direct3D12,  eShaderType::Fragment,  (uint8_t *)fs_default_d3d12,     sizeof(fs_default_d3d12));
    Add("Default", bgfx::RendererType::OpenGL,      eShaderType::Fragment,  (uint8_t *)fs_default_glsl,      sizeof(fs_default_glsl));
    Add("Default", bgfx::RendererType::Metal,       eShaderType::Fragment,  (uint8_t *)fs_default_metal,     sizeof(fs_default_metal));
    Add("Default", bgfx::RendererType::Vulkan,      eShaderType::Fragment,  (uint8_t *)fs_default_vulkan,    sizeof(fs_default_vulkan));

    Add("Default", bgfx::RendererType::Direct3D9,   eShaderType::Vertex,    (uint8_t *)vs_default_d3d9,      sizeof(vs_default_d3d9));
    Add("Default", bgfx::RendererType::Direct3D11,  eShaderType::Vertex,    (uint8_t *)vs_default_d3d11,     sizeof(vs_default_d3d11));
    Add("Default", bgfx::RendererType::Direct3D12,  eShaderType::Vertex,    (uint8_t *)vs_default_d3d12,     sizeof(vs_default_d3d12));
    Add("Default", bgfx::RendererType::OpenGL,      eShaderType::Vertex,    (uint8_t *)vs_default_glsl,      sizeof(vs_default_glsl));
    Add("Default", bgfx::RendererType::Metal,       eShaderType::Vertex,    (uint8_t *)vs_default_metal,     sizeof(vs_default_metal));
    Add("Default", bgfx::RendererType::Vulkan,      eShaderType::Vertex,    (uint8_t *)vs_default_vulkan,    sizeof(vs_default_vulkan));
    // clang-format on

    std::vector<uint8_t> v;
    for (auto &&i : m_shaders) {
        memory::SerializeIntoVector(i.type, v, 1);
        memory::SerializeIntoVector(i.renderer, v, 1);
        memory::SerializeIntoVector(i.code_len, v);
        memory::SerializeIntoVector(i.code, v, i.code_len);
    }

    FileSystem::WriteBinaryFile("default.shader", v.data(), v.size());
    std::vector<uint8_t>().swap(v);
#endif
}