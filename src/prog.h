#pragma once
#include "render.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Prog
{
public:
    Prog(GLFWwindow *w);
    ~Prog();

    void mainloop();

private:
    GLFWwindow *m_win;
    RenderInfo m_ri;
};

