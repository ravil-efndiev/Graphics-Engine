#version 330 core

in vec3 position;
in vec4 color;

out vec4 v_Color;

uniform mat4 u_Projview;

void main()
{
	v_Color = color;
	gl_Position = u_Projview * vec4(position, 1.0);
}
