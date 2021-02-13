#include "FrameBuffer.h"

#if CURRENT_API_OPENGL
static GLenum TextureTarget(bool multisampled) {
    return multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
}

static void CreateTextures(bool multisampled, uint32_t *outID, uint32_t count) {
    glCreateTextures(TextureTarget(multisampled), count, outID);
}

static void BindTexture(bool multisampled, uint32_t id) {
    glBindTexture(TextureTarget(multisampled), id);
}

static void AttachColorTexture(uint32_t id, int samples, GLenum format, uint32_t width, uint32_t height, int index) {
    bool multisampled = samples > 1;
    if (multisampled) {
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
    } else {
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, TextureTarget(multisampled), id, 0);
}

static void AttachDepthTexture(uint32_t id, int samples, GLenum format, GLenum attachmentType, uint32_t width, uint32_t height) {
    bool multisampled = samples > 1;
    if (multisampled) {
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
    } else {
        glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }

    glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, TextureTarget(multisampled), id, 0);
}

static bool IsDepthFormat(FramebufferTextureFormat format) {
    switch (format) {
        case FramebufferTextureFormat::DEPTH24STENCIL8: return true;
    }

    return false;
}

Framebuffer::Framebuffer(const FramebufferSpecification &spec) : m_specs(spec) {
    for (auto spec : m_specs.Attachments.Attachments) {
        if (!IsDepthFormat(spec.TextureFormat))
            m_colorSpecs.emplace_back(spec);
        else
            m_depthSpecs = spec;
    }

    Invalidate();
}

Framebuffer::~Framebuffer() {
    glDeleteFramebuffers(1, &m_idx);
    glDeleteTextures(m_colorAttachments.size(), m_colorAttachments.data());
    glDeleteTextures(1, &m_depthAttachment);
}

void Framebuffer::Invalidate() {
    if (m_idx) {
        glDeleteFramebuffers(1, &m_idx);
        glDeleteTextures(m_colorAttachments.size(), m_colorAttachments.data());
        glDeleteTextures(1, &m_depthAttachment);

        m_colorAttachments.clear();
        m_depthAttachment = 0;
    }

    glCreateFramebuffers(1, &m_idx);
    glBindFramebuffer(GL_FRAMEBUFFER, m_idx);

    bool multisample = m_specs.Samples > 1;

    // Attachments
    if (m_colorSpecs.size()) {
        m_colorAttachments.resize(m_colorSpecs.size());
        CreateTextures(multisample, m_colorAttachments.data(), m_colorAttachments.size());

        for (size_t i = 0; i < m_colorAttachments.size(); i++) {
            BindTexture(multisample, m_colorAttachments[i]);
            switch (m_colorSpecs[i].TextureFormat) {
                case FramebufferTextureFormat::RGBA8: AttachColorTexture(m_colorAttachments[i], m_specs.Samples, GL_RGBA8, m_specs.Width, m_specs.Height, i); break;
            }
        }
    }

    if (m_depthSpecs.TextureFormat != FramebufferTextureFormat::None) {
        CreateTextures(multisample, &m_depthAttachment, 1);
        BindTexture(multisample, m_depthAttachment);
        switch (m_depthSpecs.TextureFormat) {
            case FramebufferTextureFormat::DEPTH24STENCIL8:
                AttachDepthTexture(m_depthAttachment, m_specs.Samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, m_specs.Width, m_specs.Height);
                break;
        }
    }

    if (m_colorAttachments.size() > 1) {
        if (!(m_colorAttachments.size() <= 4)) {
            LOG_ERROR("No.");
        }
        GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
        glDrawBuffers(m_colorAttachments.size(), buffers);
    } else if (m_colorAttachments.empty()) {
        // Only depth-pass
        glDrawBuffer(GL_NONE);
    }

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        LOG_ERROR("Frame buffer given error.");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::Bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, m_idx);
    glViewport(0, 0, m_specs.Width, m_specs.Height);
}

void Framebuffer::Unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::Resize(uint32_t width, uint32_t height) {
    if (width == 0 || height == 0 || width > 8192 || height > 8192) {
        DEBUG_LOG_WARN("Attempted to rezize framebuffer to %d, %d.", width, height);
        return;
    }
    m_specs.Width = width;
    m_specs.Height = height;

    Invalidate();
}
#endif