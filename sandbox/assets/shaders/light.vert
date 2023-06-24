#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 v_TexCoords;
out vec3 v_Normal;
out vec3 v_FragPos;

uniform mat4 u_Projview;
uniform mat4 u_Transform;

void main()
{
    v_TexCoords = aTexCoords;    
    v_Normal = mat3(transpose(inverse(u_Transform))) * aNormal;
	v_FragPos = vec4(u_Transform * vec4(aPos, 1.f)).xyz;
    gl_Position = u_Projview * vec4(aPos, 1.0);
}
