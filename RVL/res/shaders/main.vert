#version 330 core

in vec3 position;
in vec3 color;

out vec3 out_color;

uniform mat4 projview;

void main()
{
    out_color = color;
    gl_Position = projview * vec4(position, 1.0);
}
