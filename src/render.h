#pragma once

#include "camera.h"
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>

struct RenderInfo
{
    unsigned int shader;
    glm::mat4 proj;
    const Camera *cam;
};

