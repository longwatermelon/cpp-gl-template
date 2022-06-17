/* #ifndef CAMERA_H */
/* #define CAMERA_H */

/* #include <cglm/cglm.h> */

/* struct Camera */
/* { */
/*     vec3 pos, rot; */

/*     vec3 front, up, right; */
/* }; */

/* struct Camera *cam_alloc(vec3 pos, vec3 rot); */
/* void cam_free(struct Camera *c); */

/* void cam_rot(struct Camera *c, vec3 rot); */
/* void cam_update_vectors(struct Camera *c); */

/* void cam_set_props(struct Camera *c, unsigned int shader); */

/* #endif */


#pragma once
#include <glm/glm.hpp>


class Camera
{
public:
    Camera(glm::vec3 pos, glm::vec3 rot);
    ~Camera();

    void rotate(glm::vec3 rot);
    void update_vectors();

    void set_props(unsigned int shader);

    glm::vec3 pos() const { return m_pos; }
    glm::vec3 rot() const { return m_rot; }

    glm::vec3 front() const { return m_front; }
    glm::vec3 up() const { return m_up; }
    glm::vec3 right() const { return m_right; }

private:
    glm::vec3 m_pos, m_rot;
    glm::vec3 m_front, m_up, m_right;
};

