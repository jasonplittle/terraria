#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>


#include "Renderer.hpp"
#include "Rectangle.hpp"

#include "Input.hpp"




void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    
    if (action == GLFW_PRESS)
    {

    }
    else if (action == GLFW_RELEASE)
    {

    }
    else
    {
        return;
    }

}



int main()
{
    std::cout << "Starting Application..." << std::endl;

    GLFWwindow* window;

    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(960, 540, "Terraria", nullptr, nullptr);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) return -1;
    std::cout << glGetString(GL_VERSION) << std::endl;


    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    Renderer renderer;
    renderer.EnableBlending();

    Rectangle rect = Rectangle(0.0f, 0.0f, 100.0f, 150.0f, { 0.18f, 0.6f, 0.96f, 0.5f });

    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();

        if (Input::Instance().IsKeyPressed(window, GLFW_KEY_UP))
        {
            rect.UpdatePosition(0.0f, 5.0f);
        }
        if (Input::Instance().IsKeyPressed(window, GLFW_KEY_DOWN))
        {
            rect.UpdatePosition(0.0f, -5.0f);
        }
        if (Input::Instance().IsKeyPressed(window, GLFW_KEY_LEFT))
        {
            rect.UpdatePosition(-5.0f, 0.0f);
        }
        if (Input::Instance().IsKeyPressed(window, GLFW_KEY_RIGHT))
        {
            rect.UpdatePosition(5.0f, 0.0f);
        }

        rect.Draw(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f));

        glfwSwapBuffers(window);
		glfwPollEvents();
    }



    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();

    return 0;
}