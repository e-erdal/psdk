#include "Shader.h"

#include "filesystem/FileSystem.h"

#include <glm/gtc/type_ptr.hpp>

static GLenum ShaderTypeFromString(const std::string &type) {
    if (type == "vertex")
        return GL_VERTEX_SHADER;
    if (type == "fragment" || type == "pixel")
        return GL_FRAGMENT_SHADER;

    return 0;
}

Shader::Shader(const std::string &path) {
    std::string src = FileSystem::ReadTextFile(path.c_str());
    auto shaders = Parse(src);
    Compile(shaders);

    m_name = FileSystem::GetFileName(path);
}

Shader::Shader(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc) {
}

Shader::~Shader() {
}

void Shader::Bind() {
    glUseProgram(m_idx);
}

void Shader::Unbind() {
    glUseProgram(0);
}

void Shader::SetInt(const std::string &name, int value) {
    glUniform1i(FindUnifrom(name), value);
}

void Shader::SetIntArray(const std::string &name, int *values, uint32_t count) {
    glUniform1iv(FindUnifrom(name), count, values);
}

void Shader::SetFloat(const std::string &name, float value) {
    glUniform1f(FindUnifrom(name), value);
}

void Shader::SetVec2(const std::string &name, const glm::vec2 &value) {
    glUniform2f(FindUnifrom(name), value.x, value.y);
}

void Shader::SetVec3(const std::string &name, const glm::vec3 &value) {
    glUniform3f(FindUnifrom(name), value.x, value.y, value.y);
}

void Shader::SetVec4(const std::string &name, const glm::vec4 &value) {
    glUniform4f(FindUnifrom(name), value.x, value.y, value.y, value.z);
}

void Shader::SetMat4(const std::string &name, const glm::mat4 &value) {
    glUniformMatrix4fv(FindUnifrom(name), 1, GL_FALSE, glm::value_ptr(value));
}

int Shader::FindUnifrom(const std::string &name) {
    return glGetUniformLocation(m_idx, name.c_str());
}

std::unordered_map<GLenum, std::string> Shader::Parse(const std::string &source) {
    std::unordered_map<GLenum, std::string> src;

    const char *typeToken = "#type";
    size_t typeTokenLength = strlen(typeToken);
    size_t pos = source.find(typeToken, 0); //Start of shader type declaration line
    while (pos != -1) {
        size_t eol = source.find_first_of("\r\n", pos); //End of shader type declaration line

        if (eol == -1)
            LOG_ERROR("Syntax error.");

        size_t begin = pos + typeTokenLength + 1; //Start of shader type name (after "#type " keyword)
        std::string type = source.substr(begin, eol - begin);
        if (!ShaderTypeFromString(type))
            LOG_ERROR("Invalid shader type.");

        size_t nextLinePos = source.find_first_not_of("\r\n", eol); //Start of shader code after shader type declaration line

        if (nextLinePos == -1)
            LOG_ERROR("Syntax error.");

        pos = source.find(typeToken, nextLinePos); //Start of next shader type declaration line

        src[ShaderTypeFromString(type)] = (pos == -1) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
    }

    return src;
}

void Shader::Compile(const std::unordered_map<GLenum, std::string> &shaderSources) {
    uint32_t program = glCreateProgram();
    uint32_t shaderIDs[2];
    int idx = 0;

    for (auto &&i : shaderSources) {
        uint32_t type = i.first;
        const char *src = i.second.c_str();

        uint32_t shader = glCreateShader(type);
        glShaderSource(shader, 1, &src, 0);
        glCompileShader(shader);

        // error message
        int result = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

        if (!result) {
            int texLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &texLen);

            if (texLen > 0) {
                std::vector<char> msg(texLen + 1);
                glGetShaderInfoLog(shader, texLen, NULL, &msg[0]);
                LOG_ERROR("%s", &msg[0]);
            }
        }

        glAttachShader(program, shader);
        shaderIDs[idx++] = shader;
    }

    m_idx = program;

    // linking but in glsl
    glLinkProgram(program);

    int result = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int *)&result);

    if (!result) {
        int texLen = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &texLen);

        if (texLen > 0) {
            std::vector<char> msg(texLen + 1);
            glGetProgramInfoLog(program, texLen, NULL, &msg[0]);
            LOG_ERROR("%s", &msg[0]);
        }

        glDeleteProgram(program);

        for (auto id : shaderIDs) glDeleteShader(id);
    }

    for (auto id : shaderIDs) {
        glDetachShader(program, id);
        glDeleteShader(id);
    }
}