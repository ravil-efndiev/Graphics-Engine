#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_Color;
in vec2 v_TexCoords;
in float v_TexIndex;

uniform sampler2D u_Textures[16];

void main()
{
	color = texture(u_Textures[int(v_TexIndex)], v_TexCoords) * v_Color;
}
