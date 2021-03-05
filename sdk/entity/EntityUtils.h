//
// Created on March 1st 2021 by loanselot1.
//
// Purpose:
//

#pragma once

#include "pch.h"

#include "Entity.h"

#include "component/RectRenderComponent.h"

extern Entity *CreateRectEntity(Entity *parent, const glm::vec2 &pos, const glm::vec2 &size);

extern void RenderAllEntities(Entity *parent);
extern void UpdateAllEntities(Entity *parent, float deltaTime);