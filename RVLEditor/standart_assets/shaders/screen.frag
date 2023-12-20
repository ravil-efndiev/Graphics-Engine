#version 330 core
out vec4 FragColor;
  
in vec2 v_TexCoords;

uniform sampler2D u_ScreenTexture;

void main()
{ 
    const int pixelSize = 1;

    float x = int(gl_FragCoord.x) % pixelSize;
    float y = int(gl_FragCoord.y) % pixelSize;

    x = floor(pixelSize / 2.0) - x + gl_FragCoord.x;
    y = floor(pixelSize / 2.0) - y + gl_FragCoord.y;

    FragColor = texture(u_ScreenTexture, vec2(x, y) / textureSize(u_ScreenTexture, 0).xy) * vec4(0.4, 0.3, 0.5, 1.0);
}
