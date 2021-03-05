#include "GameApp.h"

#include "GUI/MainMenu.h"

bool GameApp::Init() {
    MainMenuCreate(GetEntityRoot());

    return true;
}

void GameApp::Kill() {
}

void GameApp::Update() {
}