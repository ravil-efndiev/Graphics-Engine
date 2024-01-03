#version 330 core
layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_TexCoord;
layout (location = 3) in vec3 a_instanceUVScale;
layout (location = 4) in mat4 a_instanceTf;

out vec2 v_TexCoords;
out vec3 v_Normal;
out vec3 v_FragPos;

uniform mat4 u_Projview;

void main()
{
    v_TexCoords = a_TexCoord * a_instanceUVScale.xy; 
    v_Normal = mat3(transpose(inverse(a_instanceTf))) * a_Normal;
	v_FragPos = vec4(a_instanceTf * vec4(a_Pos, 1.f)).xyz;

    gl_Position = u_Projview * a_instanceTf * vec4(a_Pos, 1.0);
}
