#version 330 core

in vec3 position;

uniform vec4 u_Color;
uniform mat4 u_Transform;
uniform mat4 u_Projview;

out vec4 o_Color;

void main()
{
    o_Color = u_Color;
    gl_Position = u_Projview * u_Transform * vec4(position, 1.0);
}
