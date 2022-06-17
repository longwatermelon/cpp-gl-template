#include "prog.h"
#include "shader.h"
#include <glm/ext/matrix_clip_space.hpp>


Prog::Prog(GLFWwindow *w)
    : m_win(w)
{
    m_ri.shader = shader_create("shaders/basic_v.glsl", "shaders/basic_f_diffuse.glsl");
    m_ri.view = glm::mat4(1.f);
    glm::perspective(glm::radians(45.f), 800.f / 600.f, .1f, 100.f);
}


Prog::~Prog()
{
    glDeleteShader(m_ri.shader);
}


void Prog::mainloop()
{
    while (!glfwWindowShouldClose(m_win))
    {
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers(m_win);
        glfwPollEvents();
    }
}

