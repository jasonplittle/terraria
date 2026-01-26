#include <iostream>
#include <chrono>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>


#include "Renderer.hpp"

#include "Input.hpp"

#include "Player.hpp"
#include "PlayerRenderer.hpp"




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

    Player player = Player();
    PlayerRenderer playerRenderer = PlayerRenderer();

    float lastTime = glfwGetTime();
    float currentTime;
    float dt;

    bool isMovingUp = false;
    bool isMovingDown = false;
    bool isMovingLeft = false;
    bool isMovingRight = false;

    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();

        isMovingUp = false;
        isMovingDown = false;
        isMovingLeft = false;
        isMovingRight = false;

        if (Input::Instance().IsKeyPressed(window, GLFW_KEY_UP))
        {
            isMovingUp = true;
        }
        if (Input::Instance().IsKeyPressed(window, GLFW_KEY_DOWN))
        {
            isMovingDown = true;
        }
        if (Input::Instance().IsKeyPressed(window, GLFW_KEY_LEFT))
        {
            isMovingLeft = true;
        }
        if (Input::Instance().IsKeyPressed(window, GLFW_KEY_RIGHT))
        {
            isMovingRight = true;
        }

        currentTime = glfwGetTime();
        dt = currentTime - lastTime;
        lastTime = currentTime;

        player.Update(dt, isMovingUp, isMovingDown, isMovingLeft, isMovingRight);
        playerRenderer.Render(player);

        glfwSwapBuffers(window);
		glfwPollEvents();
    }



    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();

    return 0;
}
