#version 330 core

layout(location = 0) out vec4 FragColor;

in vec4 v_Color;
in vec3 v_Normal;
in vec3 v_FragPos;

uniform vec4 u_ViewPos;
uniform vec4 u_Direction;

void main()
{
    vec3 lightColor = vec3(0.3, 0.7, 0.5);

    float ambientStrength = 0.2;
    float specularStrength = 1.0;
    
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(v_Normal);
    vec3 lightDir = normalize(vec3(u_Direction));

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    vec3 viewDir = normalize(vec3(u_ViewPos.x, u_ViewPos.y, u_ViewPos.z) - v_FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128);
    vec3 specular = specularStrength * spec * lightColor;  

    vec3 result = (ambient + diffuse + specular) * vec3(v_Color);
    FragColor = vec4(result, 1.0);
}
