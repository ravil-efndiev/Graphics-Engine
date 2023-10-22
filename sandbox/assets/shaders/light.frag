#version 330 core
out vec4 FragColor;

in vec2 v_TexCoords;
in vec3 v_Normal;
in vec3 v_FragPos;

uniform vec3 u_ViewPos;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct DirectionalLight {
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;  
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	
    float constant;
    float linear;
    float quadratic;
}; 

uniform Material u_Material;
uniform DirectionalLight u_DirectionalLight;
uniform PointLight u_PointLight;

vec3 CalcDirLight(DirectionalLight light, Material mat, vec3 norm, vec3 viewDir)
{ 
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), mat.shininess);

    vec3 ambient = light.ambient * mat.ambient * vec3(texture(texture_diffuse1, v_TexCoords));
    vec3 diffuse = light.diffuse * (diff * mat.diffuse) * vec3(texture(texture_diffuse1, v_TexCoords));
    vec3 specular = light.specular * (mat.specular * spec) * vec3(texture(texture_specular1, v_TexCoords));
   
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, Material mat, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), mat.shininess);

    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));    

    vec3 ambient  = light.ambient  * mat.ambient * vec3(texture(texture_diffuse1, v_TexCoords));
    vec3 diffuse  = light.diffuse  * (mat.diffuse  * diff) * vec3(texture(texture_diffuse1, v_TexCoords));
    vec3 specular = light.specular * (mat.specular * spec) * vec3(texture(texture_specular1, v_TexCoords));

    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
} 

void main()
{    
    vec3 norm = normalize(v_Normal);
    vec3 viewDir = normalize(u_ViewPos - v_FragPos);

    vec3 result = CalcDirLight(u_DirectionalLight, u_Material, norm, viewDir);
    result += CalcPointLight(u_PointLight, u_Material, norm, v_FragPos, viewDir);

    FragColor = vec4(result, 1.0);
}
