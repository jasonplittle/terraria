#shader vertex
#version 330 core

layout(location = 0) in vec4 a_position;
layout(location = 1) in vec2 a_texCoord;

uniform mat4 u_MVP;
uniform vec4 u_UV;

out vec2 v_texCoord;

void main()
{
    gl_Position = u_MVP * a_position;
    // v_texCoord = a_texCoord;
    v_texCoord = mix(u_UV.xy, u_UV.zw, a_texCoord);
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_texCoord;
uniform sampler2D u_Texture;

void main()
{
    color = texture(u_Texture, v_texCoord);
    // color = vec4(1.0, 1.0, 1.0, 1.0);
};