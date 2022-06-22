#include "camera.h"
#include "shader.h"
#include <string>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>


Camera::Camera(glm::vec3 pos, glm::vec3 rot)
    : m_pos(pos), m_rot(rot)
{
    update_vectors();
}


Camera::~Camera()
{
}


void Camera::move(glm::vec3 dir)
{
    m_pos += dir;
}


void Camera::rotate(glm::vec3 rot)
{
    m_rot += rot;

    glm::vec3 deg = glm::degrees(m_rot);

    if (deg.z > 90.f) deg.z = 90.f;
    if (deg.z < -90.f) deg.z = -90.f;

    m_rot = glm::radians(deg);

    update_vectors();
}


void Camera::update_vectors()
{
    glm::quat yaw(glm::vec3(0.f, m_rot.y, 0.f));
    glm::quat pitch(glm::vec3(0.f, 0.f, m_rot.z));
    glm::quat quat = glm::normalize(yaw * pitch);

    glm::vec3 front = quat * glm::vec3(1.f, 0.f, 0.f);

    glm::vec3 right = glm::cross(front, quat * glm::vec3(0.f, 1.f, 0.f));
    glm::vec3 up = glm::cross(right, front);

    m_front = glm::normalize(front);
    m_right = glm::normalize(right);
    m_up = glm::normalize(up);
}


void Camera::set_props(unsigned int shader)
{
    shader_vec3(shader, std::string("viewPos"), m_pos);
}


glm::mat4 Camera::view() const
{
    return glm::lookAt(m_pos, m_pos + m_front, m_up);
}

