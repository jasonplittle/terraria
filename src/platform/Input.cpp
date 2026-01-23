#include "Input.hpp"


bool Input::IsKeyPressed(GLFWwindow *window, int keycode)
{
    auto state = glfwGetKey(window, keycode);
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}