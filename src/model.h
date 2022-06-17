/* #ifndef MODEL_H */
/* #define MODEL_H */

/* #include "util.h" */
/* #include "mesh.h" */
/* #include <limits.h> */
/* #include <assimp/scene.h> */

/* struct Model */
/* { */
/*     vec3 pos; */

/*     struct Mesh **meshes; */
/*     size_t nmeshes; */

/*     char dir[PATH_MAX]; */

/*     struct Texture **textures_loaded; */
/*     size_t ntextures_loaded; */

/*     mat4 translation, rotation; */
/* }; */

/* struct Model *model_alloc(vec3 pos, const char *path); */
/* void model_free(struct Model *m); */

/* void model_render(struct Model *m, RenderInfo *ri); */

/* void model_move(struct Model *m, vec3 dir); */
/* void model_rot(struct Model *m, float rad, vec3 axis); */

/* void model_process_node(struct Model *m, struct aiNode *node, const struct aiScene *sc); */
/* struct Mesh *model_process_mesh(struct Model *m, struct aiMesh *mesh, const struct aiScene *sc); */

/* struct Texture **model_load_mat_textures(struct Model *m, struct aiMaterial *mat, enum aiTextureType type, int ttype, size_t *ntextures); */

/* #endif */

#pragma once
#include "mesh.h"
#include <assimp/scene.h>

class Model
{
public:
    Model(glm::vec3 pos, const std::string &path);
    ~Model();

    void render(RenderInfo *ri);

    void move(glm::vec3 dir);
    void rotate(float rad, glm::vec3 axis);

    void process_node(aiNode *node, const aiScene *sc);
    std::unique_ptr<Mesh> process_mesh(aiMesh *mesh, const aiScene *sc);

    std::vector<Texture*> load_mat_textures(aiMaterial *mat, aiTextureType type, TextureType ttype);

private:
    glm::vec3 m_pos;
    std::string m_dir;

    std::vector<std::unique_ptr<Mesh>> m_meshes;
    std::vector<std::unique_ptr<Texture>> m_textures;

    glm::mat4 m_translation, m_rotation;
};

