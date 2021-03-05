#include "MainMenu.h"

Entity *MainMenuCreate(Entity *parent) {
    Entity *bg = parent->AddEntity(new Entity);

    CreateRectEntity(bg, { 100.f, 100.f }, { 100.f, 100.f });

    return bg;
}