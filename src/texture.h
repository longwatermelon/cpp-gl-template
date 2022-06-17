/* #ifndef TEXTURE_H */
/* #define TEXTURE_H */

/* #include "shader.h" */
/* #include <limits.h> */

/* enum { TEXTURETYPE_DIFFUSE, TEXTURETYPE_SPECULAR }; */

/* struct Texture */
/* { */
/*     int type; */
/*     unsigned int id; */

/*     char path[PATH_MAX]; */
/* }; */

/* struct Texture *tex_alloc(const char *path, int type); */
/* void tex_free(struct Texture *t); */

/* void tex_bind(struct Texture *t, unsigned int slot); */

/* #endif */

#pragma once
#include "shader.h"
#include <string>
#include <limits>

enum class TextureType
{
    DIFFUSE,
    SPECULAR
};

class Texture
{
public:
    Texture(const std::string &path, TextureType type);
    ~Texture();

    void bind(unsigned int slot);

    TextureType type() const { return m_type; }
    std::string path() const { return m_path; }

    unsigned int id() const { return m_id; }

private:
    TextureType m_type;
    unsigned int m_id;

    std::string m_path;
};

