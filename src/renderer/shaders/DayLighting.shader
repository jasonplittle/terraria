#shader vertex
#version 330 core

layout(location = 0) in vec2 a_position;

out vec2 v_ScreenPos;

void main()
{
    gl_Position = vec4(a_position, 0.0, 1.0);
    v_ScreenPos = a_position;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_ScreenPos;

uniform vec2 u_HalfWorldSize;
uniform vec2 u_CameraPos;

uniform float u_Lighting;
uniform float u_TorchRadius;
uniform vec2 u_TorchPositions[16];
uniform int u_TorchCount;


void main()
{
    // Reconstruct world position from fullscreen quad
    vec2 worldPos = vec2(
        u_CameraPos.x + v_ScreenPos.x * u_HalfWorldSize.x,
        u_CameraPos.y + v_ScreenPos.y * u_HalfWorldSize.y
    );

    float lightAmount = 0.0;

    for (int i = 0; i < u_TorchCount; i++)
    {
        float dist = distance(worldPos, u_TorchPositions[i]);

        float t = dist / u_TorchRadius;

        // hot core (bright center)
        float core = 1.0 - smoothstep(0.0, 0.35, t);

        // softer outer glow
        float glow = 1.0 - smoothstep(0.2, 1.0, t);

        float intensity = core * 1.0 + glow * 0.5;

        lightAmount += intensity;
    }

    lightAmount = clamp(lightAmount, 0.0, 1.0);

    // --- color shaping ---

    vec3 darkColor = vec3(0.0, 0.0, 0.05);

    // warm torch center
    vec3 warmColor = vec3(1.0, 0.55, 0.2);

    // cooler edge tint
    vec3 coolTint = vec3(0.2, 0.2, 0.35);

    vec3 torchColor = mix(coolTint, warmColor, lightAmount);

    vec3 finalColor = mix(darkColor, torchColor, lightAmount);

    float finalAlpha = u_Lighting * (1.0 - lightAmount);

    color = vec4(finalColor, finalAlpha);
}


// void main()
// {
//     vec2 worldPos = vec2(
//         u_CameraPos.x + v_ScreenPos.x * u_HalfWorldSize.x,
//         u_CameraPos.y + v_ScreenPos.y * u_HalfWorldSize.y
//     );

//     float lightAmount = 0.0;

//     for (int i = 0; i < u_TorchCount; i++)
//     {
//         float dist = distance(worldPos, u_TorchPositions[i]);
//         float intensity = 1.0 - smoothstep(0.0, u_TorchRadius, dist);
//         lightAmount += intensity;
//     }

//     lightAmount = clamp(lightAmount, 0.0, 1.0);
//     float finalAlpha = u_Lighting * (1.0 - lightAmount);
//     color = vec4(0.0, 0.0, 0.05, finalAlpha);
// };
