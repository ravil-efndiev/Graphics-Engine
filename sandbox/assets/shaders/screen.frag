#version 330 core
out vec4 FragColor;
  
in vec2 v_TexCoords;

uniform sampler2D u_ScreenTexture;

void main()
{ 
    const int pixelSize = 4;

    float x = int(gl_FragCoord.x) % pixelSize;
    float y = int(gl_FragCoord.y) % pixelSize;

    x = floor(pixelSize / 2.0) - x;
    y = floor(pixelSize / 2.0) - y;

    x = gl_FragCoord.x + x;
    y = gl_FragCoord.y + y;

    FragColor = texture(u_ScreenTexture, vec2(x, y) / textureSize(u_ScreenTexture, 0).xy) * vec4(0.6, 0.3, 0.3, 1.0);
}
