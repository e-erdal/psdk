//
// Created on February 11th 2021 by loanselot1.
//

#include "pch.h"

#include "app/App.h"

ENTRY_POINT() {
    AppInfo cfg;
    cfg.appName = "BareBones";
    cfg.verMaj = 1;
    cfg.verMin = 0;
    cfg.verBuild = 0;

    cfg.title = "Game";
    cfg.windowRes = { 1024, 768 };
    cfg.windowFlags = eWindowFlags::NONE;

    App *app = new App(cfg);
    app->Run();

    delete app;
}