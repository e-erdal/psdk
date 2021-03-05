//
// Created on March 5th 2021 by loanselot1.
//
// Purpose: Game application entrypoint.
//

#pragma once

#include "app/App.h"

class GameApp : public App {
public:
    GameApp(){};
    ~GameApp(){};

    bool Init() override;
    void Kill() override;
    void Update() override;

private:
};