#version 330 core

layout(location = 0) out vec4 FragColor;

in vec4 v_Color;

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * vec3(0.7, 0.4, 0.5);

    FragColor = vec4(ambient, 1.0) * v_Color;
}
