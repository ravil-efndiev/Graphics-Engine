#version 330 core

in vec3 position;
in vec2 coords;

out vec2 TexCoord;

uniform mat4 u_Projview;
uniform mat4 u_Transform;

void main()
{
    gl_Position = u_Projview * u_Transform *  vec4(position, 1.0);
    TexCoord = coords;
}
