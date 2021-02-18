#include "Camera.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

Camera::Camera(int x, int y, int w, int h) : m_position(x, y), m_screenSize(w, h) {
    CalculateTransformation();
}

void Camera::CalculateTransformation() {
    m_projMatrix = glm::ortho(0.0f, (float)m_screenSize.x, (float)m_screenSize.y, 0.0f, 0.1f, 1000.0f);

    m_projMatrix[3].z = 1;

    m_viewMatrix = glm::inverse(
        glm::translate(glm::mat4(1.0f), glm::vec3(m_position.x, m_position.y, 0.f)) * glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation), glm::vec3(0, 0, 1)));

    m_VPM = m_projMatrix * m_viewMatrix;

    bgfx::setViewTransform(0, glm::value_ptr(m_viewMatrix), glm::value_ptr(m_projMatrix));
}