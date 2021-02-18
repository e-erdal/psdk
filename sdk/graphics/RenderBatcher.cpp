#include "RenderBatcher.h"

#include "ShaderManager.h"
#include "app/App.h"

static RenderBatcherData *rbd = 0;
static uint32_t maxVertices = 100000;

void RenderBatcher::Initialize() {
    rbd = new (RenderBatcherData);
    rbd->defaultLayout.begin()
        .add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float)
        .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
        .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Float, true)
        .add(bgfx::Attrib::TexCoord1, 2, bgfx::AttribType::Float)
        .end();

    rbd->defaultProgram = bgfx::createUniform("u_texture", bgfx::UniformType::Sampler);

    uint32_t wtd = 0xffffffff;
    rbd->whiteTexture = new Texture(1, 1);
    rbd->whiteTexture->Update(&wtd, 4);

    uint32_t *quads = new uint32_t[maxVertices * 6];
    uint32_t offset = 0;

    for (uint32_t i = 0; i < (maxVertices * 6); i += 6) {
        quads[i + 0] = offset + 0;
        quads[i + 1] = offset + 1;
        quads[i + 2] = offset + 2;

        quads[i + 3] = offset + 2;
        quads[i + 4] = offset + 3;
        quads[i + 5] = offset + 0;

        offset += 4;
    }

    rbd->ibh = bgfx::createIndexBuffer(bgfx::copy(quads, maxVertices * 6 * sizeof(uint32_t)), BGFX_BUFFER_INDEX32);
    delete[] quads;

    rbd->defaultShader = GetShaderManager()->LoadProgram("Default");
}

void RenderBatcher::NewFrame() {
    rbd->indexes = 0;

    // clear the map
    for (auto &&texture : rbd->batchEvents) std::vector<VertexInfo>().swap(texture.second);

    rbd->batchEvents.clear();
}

void RenderBatcher::EndFrame() {
    Flush();
}

static bgfx::TransientVertexBuffer tvb;
void RenderBatcher::Flush() {
    for (auto &&events : rbd->batchEvents) {
        Texture *texture = events.first;
        auto &vertexes = events.second;

        if (vertexes.size() > 0) {
            bgfx::allocTransientVertexBuffer(&tvb, vertexes.size(), rbd->defaultLayout);
            memcpy(tvb.data, &vertexes[0], vertexes.size() * sizeof(VertexInfo));

            bgfx::setVertexBuffer(0, &tvb, 0, vertexes.size());

            bgfx::setTexture(0, rbd->defaultProgram, texture->GetHandle());

            uint32_t count = rbd->indexes ? rbd->indexes : maxVertices * 6;
            bgfx::setIndexBuffer(rbd->ibh, 0, count);

            bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_BLEND_ALPHA);

            bgfx::submit(0, rbd->defaultShader);
        }
    }
}

void RenderBatcher::ResetBatch() {
    Flush();

    rbd->indexes = 0;

    // clear the map
    for (auto &&texture : rbd->batchEvents) std::vector<VertexInfo>().swap(texture.second);

    rbd->batchEvents.clear();
}

void RenderBatcher::Submit(Texture *texture, const glm::mat4 &transform, const glm::mat4x2 &uvs, const glm::vec4 &color) {
    for (size_t i = 0; i < 4; i++) {
        VertexInfo info;
        info.pos = transform * g_defPos[i];
        info.color = color;
        info.uvs = uvs[i];
        info.extra = { 1, 1 };
        rbd->batchEvents[texture].push_back(info);
    }

    rbd->indexes += 6;
}
