//
// Created on February 28th 2021 by loanselot1.
//
// Purpose:
//

#pragma once

#include "pch.h"

#include "Entity.h"
#include "EntityComponent.h"

#include "graphics/Texture.h"

class RectRenderComponent : public EntityComponent {
public:
    RectRenderComponent(){};
    virtual ~RectRenderComponent(){};

    virtual void OnAdd(Entity *entity);
    virtual void OnRemove();

    enum eVisualStyle {
        STYLE_NORMAL, //filled rect
        STYLE_BORDER_ONLY
    };

private:
    void OnRender(VariantList *vList);

    glm::vec2 m_pos2d;
    glm::vec2 m_size2d;
    glm::vec2 m_scale2d;

    glm::vec3 m_color;

    glm::mat4 m_transform;

    Texture *m_texture;
};