#version 330 core

in vec3 a_Position;
in vec4 a_Color;
in vec2 a_TexCoords;
in float a_TexIndex;

out vec4 v_Color;
out vec2 v_TexCoords;
out float v_TexIndex;

uniform mat4 u_Projview;

void main()
{
	v_Color = a_Color;
	v_TexCoords = a_TexCoords;
	v_TexIndex = a_TexIndex;
	gl_Position = u_Projview * vec4(a_Position, 1.0);
}
