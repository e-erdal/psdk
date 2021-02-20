//
// Created on February 20th 2021 by loanselot1.
//
// Purpose: Global message handler.
//

#pragma once

#include "pch.h"

enum class MessageTarget {
    GAME,   // generic global game-specific messages
    GUI,    // these come from GUI events like clicks
    ENTITY, // delivered directly to specific entities
};

// clang-format off
enum class MessageType {
    // must be in order
    CLICK_START,
    CLICK_END,
};
// clang-format on

class MessageManager {
public:
    MessageManager();
    ~MessageManager();
};