#version 330 core

in vec3 position;
in vec3 color;
in vec2 coords;

out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 projview;

void main()
{
    gl_Position = projview * vec4(position, 1.0);
    ourColor = color;
    TexCoord = coords;
}
