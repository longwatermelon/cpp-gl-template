/* #ifndef LIGHT_H */
/* #define LIGHT_H */

/* #include "texture.h" */
/* #include <cglm/cglm.h> */

/* typedef struct */
/* { */
/*     vec3 ambient, diffuse, specular; */
/* } Phong; */

/* Phong phong(vec3 ambient, vec3 diffuse, vec3 specular); */

/* typedef struct */
/* { */
/*     float constant, linear, quadratic; */
/* } Attenuation; */

/* enum { LIGHT_POINT, LIGHT_SPOTLIGHT }; */

/* struct Light */
/* { */
/*     int type; */

/*     vec3 pos; */
/*     Phong col; */
/*     Attenuation att; */

/*     // spotlight */
/*     vec3 spotlight_dir; */
/*     float spotlight_cutoff, spotlight_outer_cutoff; */
/* }; */

/* struct Light *light_alloc(vec3 pos, Phong col, Attenuation att); */
/* void light_free(struct Light *l); */

/* struct Light *light_spotlight(struct Light *l, vec3 dir, float cutoff, float outer_cutoff); */

/* void light_set_props(struct Light *l, unsigned int shader, int idx); */

/* #endif */

#pragma once

#include "texture.h"
#include <glm/glm.hpp>

struct Phong
{
    Phong(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
        : ambient(ambient), diffuse(diffuse), specular(specular) {}

    glm::vec3 ambient, diffuse, specular;
};

struct Attenuation
{
    Attenuation(float constant, float linear, float quadratic)
        : constant(constant), linear(linear), quadratic(quadratic) {}

    float constant, linear, quadratic;
};

enum class LightType
{
    POINT = 0,
    SPOTLIGHT = 1
};

class Light
{
public:
    Light(glm::vec3 pos, Phong col, Attenuation att);
    ~Light();

    void set_props(unsigned int shader, int idx);

    Light &make_spotlight(glm::vec3 dir, float cutoff, float outer_cutoff);

private:
    LightType m_type;

    glm::vec3 m_pos;
    Phong m_col;
    Attenuation m_att;

    glm::vec3 m_spotlight_dir;
    float m_spotlight_cutoff, m_spotlight_outer_cutoff;
};

