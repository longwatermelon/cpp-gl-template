#include "prog.h"
#include "light.h"
#include "model.h"
#include <vector>
#include <iostream>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <stb/stb_image.h>


Prog::Prog(GLFWwindow *w)
    : m_win(w)
{
    m_ri.shader = shader_create("shaders/basic_v.glsl", "shaders/basic_f.glsl");
    m_ri.view = glm::mat4(1.f);
    m_ri.proj = glm::perspective(glm::radians(45.f), 800.f / 600.f, .1f, 100.f);

    m_cam = std::make_unique<Camera>(glm::vec3(0.f, 0.f, 5.f), glm::vec3(glm::radians(-90.f), 0.f, 0.f));
    std::cout << m_cam->front().x << ' ' << m_cam->front().y << ' ' << m_cam->front().z << "\n";

    stbi_set_flip_vertically_on_load(true);
}


Prog::~Prog()
{
    glDeleteShader(m_ri.shader);
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

    std::unique_ptr<Model> m = std::make_unique<Model>(glm::vec3(0.f, 0.f, 0.f), "res/backpack/backpack.obj");
    std::cout << "Loaded model\n";

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(m_win))
    {
        events();

        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_ri.view = glm::lookAt(m_cam->pos(), m_cam->pos() + m_cam->front(), m_cam->up());
        m_cam->set_props(m_ri.shader);

        for (size_t i = 0; i < lights.size(); ++i)
            lights[i].set_props(m_ri.shader, i);

        m->render(&m_ri);

        glfwSwapBuffers(m_win);
        glfwPollEvents();
    }
}


void Prog::events()
{
    float move = .05f;
    float rot = 2.f;

    glm::vec3 front = m_cam->front() * move;
    front[1] = 0.f;

    glm::vec3 right = m_cam->right() * move;
    right[1] = 0.f;

    if (glfwGetKey(m_win, GLFW_KEY_W) == GLFW_PRESS) m_cam->move(front);
    if (glfwGetKey(m_win, GLFW_KEY_S) == GLFW_PRESS) m_cam->move(-front);
    if (glfwGetKey(m_win, GLFW_KEY_A) == GLFW_PRESS) m_cam->move(-right);
    if (glfwGetKey(m_win, GLFW_KEY_D) == GLFW_PRESS) m_cam->move(right);

    if (glfwGetKey(m_win, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) m_cam->move(glm::vec3(0.f, -move, 0.f));
    if (glfwGetKey(m_win, GLFW_KEY_SPACE) == GLFW_PRESS) m_cam->move(glm::vec3(0.f, move, 0.f));

    if (glfwGetKey(m_win, GLFW_KEY_LEFT) == GLFW_PRESS)
        m_cam->rotate(glm::vec3(-rot, 0.f, 0.f));

    if (glfwGetKey(m_win, GLFW_KEY_RIGHT) == GLFW_PRESS)
        m_cam->rotate(glm::vec3(rot, 0.f, 0.f));

    if (glfwGetKey(m_win, GLFW_KEY_UP) == GLFW_PRESS)
        m_cam->rotate(glm::vec3(0.f, rot, 0.f));

    if (glfwGetKey(m_win, GLFW_KEY_DOWN) == GLFW_PRESS)
        m_cam->rotate(glm::vec3(0.f, -rot, 0.f));
}

