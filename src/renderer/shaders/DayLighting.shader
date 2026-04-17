#shader vertex
#version 330 core

layout(location = 0) in vec2 a_position;

out vec2 v_texCoord;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * vec4(a_position, 0.0, 1.0);
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform float u_Lighting;

void main()
{
    color = vec4(0.0, 0.0, 0.05, u_Lighting); // slight blue tint
};