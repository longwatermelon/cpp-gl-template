/* #ifndef MESH_H */
/* #define MESH_H */

/* #include "util.h" */
/* #include "texture.h" */
/* #include "render.h" */
/* #include <cglm/cglm.h> */

/* typedef struct */
/* { */
/*     vec3 pos, norm; */
/*     vec2 tex_coords; */
/* } Vertex; */

/* struct Mesh */
/* { */
/*     Vertex *verts; */
/*     size_t nverts; */

/*     unsigned int *indices; */
/*     size_t nindices; */

/*     struct Texture **textures; */
/*     size_t ntextures; */

/*     unsigned int vao, vb, ib; */
/* }; */

/* // Memory ownership of verts, indices, textures is transferred to mesh */
/* struct Mesh *mesh_alloc(Vertex *verts, size_t nverts, unsigned int *indices, size_t nindices, struct Texture **textures, size_t ntextures); */
/* void mesh_free(struct Mesh *m); */

/* void mesh_render(struct Mesh *m, RenderInfo *ri, mat4 model); */


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

    void render(RenderInfo *ri, glm::mat4 model);

private:
    std::vector<Vertex> m_verts;
    std::vector<unsigned int> m_indices;
    std::vector<Texture*> m_textures;

    unsigned int m_vao, m_vb, m_ib;
};

