#include "prog.h"
#include "light.h"
#include "model.h"
#include <vector>
#include <iostream>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <stb/stb_image.h>


Prog::Prog(GLFWwindow *w)
    : m_win(w), m_cam(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f))
{
    m_ri.add_shader("basic");
    m_ri.use_shader("basic");

    m_ri.proj = glm::perspective(glm::radians(45.f), 800.f / 600.f, .1f, 100.f);
    m_ri.cam = &m_cam;

    stbi_set_flip_vertically_on_load(true);
}


Prog::~Prog()
{
    m_ri.clear_shaders();
}


void Prog::mainloop()
{
    std::vector<Light> lights = {
        Light(glm::vec3(3.f, -1.f, 5.f), Phong(
            glm::vec3(.2f, .2f, .2f),
            glm::vec3(.5f, .5f, .5f),
            glm::vec3(1.f, 1.f, 1.f)
        ), Attenuation(1.f, .09f, .032f)).make_spotlight(
            glm::vec3(0.f, 0.f, -1.f),
            cosf(glm::radians(14.5f)), cosf(glm::radians(20.5f))
        ),
        Light(glm::vec3(3.f, -1.f, 5.f), Phong(
            glm::vec3(.2f, .2f, .2f),
            glm::vec3(.5f, .5f, .5f),
            glm::vec3(1.f, 1.f, 1.f)
        ), Attenuation(1.f, .09f, .032f))
    };

    Model m(glm::vec3(5.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), "res/backpack/backpack.obj");

    glEnable(GL_DEPTH_TEST);

    glfwSetCursorPos(m_win, 400.f, 300.f);
    glfwSetInputMode(m_win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    double prev_mx, prev_my;
    glfwGetCursorPos(m_win, &prev_mx, &prev_my);

    while (!glfwWindowShouldClose(m_win))
    {
        events();

        double mx, my;
        glfwGetCursorPos(m_win, &mx, &my);
        m_cam.rotate(glm::vec3(0.f, -(mx - prev_mx) / 100.f, -(my - prev_my) / 100.f));

        prev_mx = mx;
        prev_my = my;

        lights[0].move(m_cam.pos());
        lights[0].spotlight_rotate(m_cam.front());

        /* m.move(glm::vec3(0.f, 0.f, -.05f)); */
        /* m.rotate(glm::vec3(0.f, .01f, .01f)); */

        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_ri.use_shader("basic");

        m_cam.set_props(m_ri);

        for (size_t i = 0; i < lights.size(); ++i)
            lights[i].set_props(m_ri, i);

        m.render(m_ri);

        glfwSwapBuffers(m_win);
        glfwPollEvents();
    }
}


void Prog::events()
{
    float move = .05f;

    glm::vec3 front = m_cam.front() * move;
    front[1] = 0.f;

    glm::vec3 right = m_cam.right() * move;
    right[1] = 0.f;

    if (glfwGetKey(m_win, GLFW_KEY_W) == GLFW_PRESS) m_cam.move(front);
    if (glfwGetKey(m_win, GLFW_KEY_S) == GLFW_PRESS) m_cam.move(-front);
    if (glfwGetKey(m_win, GLFW_KEY_A) == GLFW_PRESS) m_cam.move(-right);
    if (glfwGetKey(m_win, GLFW_KEY_D) == GLFW_PRESS) m_cam.move(right);

    if (glfwGetKey(m_win, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) m_cam.move(glm::vec3(0.f, -move, 0.f));
    if (glfwGetKey(m_win, GLFW_KEY_SPACE) == GLFW_PRESS) m_cam.move(glm::vec3(0.f, move, 0.f));
}

