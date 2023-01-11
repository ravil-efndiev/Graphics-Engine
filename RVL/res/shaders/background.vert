#version 330 core

in vec3 position;
uniform mat4 projview;

void main()
{
    gl_Position = projview * vec4(position, 1.0);
}
