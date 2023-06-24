#version 330 core

in vec3 a_Position;
in vec4 a_Color;
in vec3 a_Normal;

out vec4 v_Color;
out vec3 v_Normal;
out vec3 v_FragPos;

uniform mat4 u_Projview;
uniform mat4 u_Transform;

void main()
{
	v_Color = a_Color;
	v_Normal = mat3(transpose(inverse(u_Transform))) * a_Normal;
	v_FragPos = vec4(u_Transform * vec4(a_Position, 1.f)).xyz;
	gl_Position = u_Projview * u_Transform * vec4(a_Position, 1.0);
}
