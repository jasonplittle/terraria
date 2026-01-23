#pragma once

#include <GLFW/glfw3.h>

class Input
{
public:
    static Input& Instance()
    {
        static Input instance;
        return instance;
    }

    Input(const Input&) = delete;
    Input& operator=(const Input&) = delete;
    Input(Input&&) = delete;
    Input& operator=(Input&&) = delete;

    bool IsKeyPressed(GLFWwindow *window, int keycode);

private:
    Input() = default;
    ~Input() = default;

};



