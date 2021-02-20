//
// Created on February 20th 2021 by loanselot1.
//
// Purpose: Global input handler.
//

#pragma once

#include "pch.h"
#include <unordered_map>

#include "input/Helpers.h"

class InputManager {
public:
    InputManager();
    ~InputManager();

    void Update();

public:
    bool IsPressed(KeyCode key);
    bool IsReleased(KeyCode key);

    bool IsMousePressed(MouseCode key);
    bool IsMouseReleased(MouseCode key);

    void ProcessKeyboard(int key, int scancode, int action, int mods);
    void ProcessMouse(int button, int action, int mods);

public:
    const glm::vec2 &GetMousePos() const {
        return m_mousePos;
    }

    const glm::vec2 &GetMouseScroll() const {
        return m_mouseScrollAxis;
    }

private:
    std::unordered_map<MouseCode, KeyState> m_mouseState;
    std::unordered_map<KeyCode, KeyState> m_keyboardState;
    KeyMods m_mods{};

    glm::vec2 m_mousePos{};
    glm::vec2 m_mouseScrollAxis{};
};