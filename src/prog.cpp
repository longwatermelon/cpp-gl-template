#include "prog.h"


Prog::Prog(GLFWwindow *w)
    : m_win(w)
{
}


Prog::~Prog()
{
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

