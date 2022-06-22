#pragma once
#include "texture.h"
#include "render.h"
#include <vector>
#include <memory>
#include <glm/glm.hpp>

struct Vertex
{
    glm::vec3 pos, norm;
    glm::vec2 tex_coords;
};

class Mesh
{
public:
    Mesh(const std::vector<Vertex> &verts, const std::vector<unsigned int> &indices, const std::vector<Texture*> &textures);
    Mesh(Mesh&&) = default;
    ~Mesh();

    void render(RenderInfo &ri, glm::mat4 model);

    void update_pos(glm::vec3 pos) { m_pos = pos; }
    void update_rot(glm::vec3 rot) { m_rot = rot; }

private:
    glm::vec3 m_pos = glm::vec3(0.f, 0.f, 0.f), m_rot = glm::vec3(0.f, 0.f, 0.f);

    std::vector<Vertex> m_verts;
    std::vector<unsigned int> m_indices;
    std::vector<Texture*> m_textures;

    unsigned int m_vao, m_vb, m_ib;
};

