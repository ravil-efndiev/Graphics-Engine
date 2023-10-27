#version 330 core
layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_TexCoord;

out vec2 v_TexCoords;
out vec3 v_Normal;
out vec3 v_FragPos;

uniform mat4 u_Projview;
uniform mat4 u_Transform;

void main()
{
    v_TexCoords = a_TexCoord;    
    v_Normal = mat3(transpose(inverse(u_Transform))) * a_Normal;
	v_FragPos = vec4(u_Transform * vec4(a_Pos, 1.f)).xyz;
    gl_Position = u_Projview * u_Transform * vec4(a_Pos, 1.0);
}
