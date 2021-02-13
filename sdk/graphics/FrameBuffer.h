//
// Created on February 13th 2021 by loanselot1.
//
// Purpose: Framebuffer main handler. From Hazel.
//

#pragma once

#include "pch.h"

enum class FramebufferTextureFormat {
    None = 0,

    // Color
    RGBA8,

    // Depth/stencil
    DEPTH24STENCIL8,

    // Defaults
    Depth = DEPTH24STENCIL8
};

struct FramebufferTextureSpecification {
    FramebufferTextureSpecification() = default;
    FramebufferTextureSpecification(FramebufferTextureFormat format) : TextureFormat(format) {
    }

    FramebufferTextureFormat TextureFormat = FramebufferTextureFormat::None;
    // TODO: filtering/wrap
};

struct FramebufferAttachmentSpecification {
    FramebufferAttachmentSpecification() = default;
    FramebufferAttachmentSpecification(std::initializer_list<FramebufferTextureSpecification> attachments) : Attachments(attachments) {
    }

    std::vector<FramebufferTextureSpecification> Attachments;
};

struct FramebufferSpecification {
    uint32_t Width = 0, Height = 0;
    FramebufferAttachmentSpecification Attachments;
    uint32_t Samples = 1;

    bool SwapChainTarget = false;
};

class Framebuffer {
public:
    Framebuffer(const FramebufferSpecification &spec);
    ~Framebuffer();

    void Invalidate();

    void Bind();
    void Unbind();

    void Resize(uint32_t width, uint32_t height);

    uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const {
        if (index < m_colorAttachments.size())
            return m_colorAttachments[index];
        else
            return 0;
    }

    const FramebufferSpecification &GetSpecification() const {
        return m_specs;
    }

private:
    uint32_t m_idx = 0;
    FramebufferSpecification m_specs;

    std::vector<FramebufferTextureSpecification> m_colorSpecs;
    FramebufferTextureSpecification m_depthSpecs = FramebufferTextureFormat::None;

    std::vector<uint32_t> m_colorAttachments;
    uint32_t m_depthAttachment = 0;
};