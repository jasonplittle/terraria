#shader vertex
#version 330 core

layout (location = 0) in vec2 aPos;   // world-space position
layout (location = 1) in vec2 aUV;    // atlas UV

uniform mat4 u_MVP;

out vec2 vUV;

void main()
{
    vUV = aUV;
    gl_Position = u_MVP * vec4(aPos, 0.0, 1.0);
}

#shader fragment
#version 330 core

in vec2 vUV;
out vec4 FragColor;

uniform sampler2D u_Atlas;

void main()
{
    // FragColor = vec4(vUV, 1.0, 1.0);
    // FragColor = texture(u_Atlas, vUV) + vec4(1.0, 1.0, 1.0, 1.0);
    FragColor = texture(u_Atlas, vUV);
}