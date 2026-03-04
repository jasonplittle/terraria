#shader vertex
#version 330 core

layout(location = 0) in vec2 a_position;
layout(location = 1) in vec2 a_texCoord;

out vec2 v_texCoord;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * vec4(a_position, 0.0, 1.0);
    v_texCoord = a_texCoord;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_texCoord;
uniform sampler2D u_Texture;

void main()
{
    color = texture(u_Texture, v_texCoord);
};