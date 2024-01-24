#include "graphicscontext.h"

// clang-format off
#include "../opengl/glad/glad.h"
#include <GLFW/glfw3.h>
// clang-format on

#include <cassert>
#include <iostream>

size_t LinuxGraphicsContext::nr_contexts = 0;

LinuxGraphicsContext::LinuxGraphicsContext()
{
    if (nr_contexts == 0)
        glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    context_handle = glfwCreateWindow(1, 1, "", nullptr, nullptr);

    bind();

    if (nr_contexts == 0) {
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cerr << "GLAD: Init failed\n";
            assert(false);
        }
    }

    nr_contexts++;
}

LinuxGraphicsContext::~LinuxGraphicsContext()
{
    nr_contexts--;

    if (nr_contexts == 0)
        glfwTerminate();
    else
        glfwDestroyWindow(context_handle);
}

void LinuxGraphicsContext::bind() const
{
    glfwMakeContextCurrent(context_handle);
}
