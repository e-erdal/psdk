#include "EntityUtils.h"

#include <glm/gtx/transform.hpp>

Entity *CreateRectEntity(Entity *parent, const glm::vec2 &pos, const glm::vec2 &size) {
    Entity *entity = 0;

    if (parent)
        entity = parent->AddEntity(new Entity());
    else
        entity = new Entity();

    EntityComponent *component = entity->AddComponent(new RectRenderComponent());

    entity->GetVar("pos2d")->Set(pos);
    entity->GetVar("size2d")->Set(size);
    entity->GetVar("color")->Set(glm::vec3({ 255.f, 255.f, 255.f }));

    entity->GetVar("transform")->Set(glm::translate(glm::mat4(1.f), { pos.x, pos.y, 1.f }) * glm::scale(glm::mat4(1.f), { size.x, size.y, 1.f }));

    return entity;
}

void RenderAllEntities(Entity *parent) {
    parent->CallFunction("OnRender", 0);

    EntityList *childs = parent->GetChildren();

    auto &itor = childs->begin();

    while (itor != childs->end()) {
        RenderAllEntities(*itor);
        itor++;
    }
}