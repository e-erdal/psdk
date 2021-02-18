//
// Created on February 13th 2021 by loanselot1.
//
// Purpose: Eye of player. Orthographic, so 2D.
//

#pragma once

#include "pch.h"

class Camera {
public:
    Camera(int x, int y, int w, int h);

    void CalculateTransformation();

    glm::ivec2 &GetScale() {
        return m_screenSize;
    }

    glm::ivec2 &GetPosition() {
        return m_position;
    }

    const glm::mat4 &GetTransform() const {
        return m_VPM;
    }

private:
    glm::ivec2 m_screenSize;
    glm::ivec2 m_position;

    glm::mat4 m_viewMatrix;
    glm::mat4 m_projMatrix;
    glm::mat4 m_VPM;

    float m_rotation = 0;
};