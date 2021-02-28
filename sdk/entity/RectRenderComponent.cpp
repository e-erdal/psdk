#include "RectRenderComponent.h"

#include "graphics/RenderBatcher.h"

void RectRenderComponent::OnAdd(Entity *entity) {
    EntityComponent::OnAdd(entity);

    m_pos2d = GetParent()->GetVar("pos2d")->GetVec2();
    m_size2d = GetParent()->GetVar("size2d")->GetVec2();
    m_scale2d = GetParent()->GetVar("scale2d")->GetVec2();
    m_transform = GetParent()->GetVar("transform")->GetMat4();

    m_color = GetParent()->GetVar("color")->GetVec3();

    GetFunction("OnRender")->sig = std::bind(&RectRenderComponent::OnRender, this, _1);
}

void RectRenderComponent::OnRemove() {
    EntityComponent::OnRemove();
}

void RectRenderComponent::OnRender(VariantList *vList) {
    RenderBatcher::DrawRectangle(m_texture, m_transform, { m_color.x / 255.f, m_color.y / 255.f, m_color.z / 255.f, 1 });
}