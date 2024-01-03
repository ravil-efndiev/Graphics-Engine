#version 330 core
out vec4 FragColor;

in vec2 v_TexCoords;
in vec3 v_Normal;
in vec3 v_FragPos;

uniform vec3 u_ViewPos;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform int u_HasTexture;

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
  
    vec3 diffuse;
    vec3 specular;
	
    float constant;
    float linear;
    float quadratic;
}; 

uniform Material u_Material;
uniform DirectionalLight u_DirectionalLight;
uniform PointLight u_PointLight[100];

uniform int u_LightsCount;

vec3 CalcDirLight(DirectionalLight light, Material mat, vec3 norm, vec3 viewDir, vec2 TexCoords)
{ 
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), mat.shininess);
    vec3 ambient, diffuse, specular;

    if (u_HasTexture == 0)
    {
        ambient  = light.ambient  * mat.ambient;
        diffuse  = light.diffuse  * (mat.diffuse  * diff);
        specular = light.specular * (mat.specular * spec);
    }
    else
    {
        ambient  = light.ambient  * mat.ambient * vec3(texture(texture_diffuse1, TexCoords));
        diffuse  = light.diffuse  * (mat.diffuse  * diff) * vec3(texture(texture_diffuse1, TexCoords));
        specular = light.specular * (mat.specular * spec) * vec3(texture(texture_specular1, TexCoords));
    }

    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, Material mat, vec3 normal, vec3 fragPos, vec3 viewDir, vec2 TexCoords)
{
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), mat.shininess);

    float dist        = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * dist + 
  			     light.quadratic * (dist * dist));    

    vec3 diffuse, specular;

    if (u_HasTexture == 0)
    {
        diffuse  = attenuation * light.diffuse  * (mat.diffuse  * diff);
        specular = attenuation * light.specular * (mat.specular * spec);
    }
    else
    {
        diffuse  = attenuation * light.diffuse  * (mat.diffuse  * diff) * vec3(texture(texture_diffuse1, TexCoords));
        specular = attenuation * light.specular * (mat.specular * spec) * vec3(texture(texture_specular1, TexCoords));
    }

    return (diffuse + specular);
} 

void main()
{    
    vec3 norm = normalize(v_Normal);
    vec3 viewDir = normalize(u_ViewPos - v_FragPos);

    vec3 fragPos = v_FragPos;
    vec2 texCoord = v_TexCoords;

    Material mat = u_Material;

    vec3 result = CalcDirLight(u_DirectionalLight, u_Material, norm, viewDir, texCoord);
    for (int i = 0; i < 100; ++i)
    {
        if (i >= u_LightsCount)
            break;

        result += CalcPointLight(u_PointLight[i], mat, norm, fragPos, viewDir, texCoord);
    }

    FragColor = vec4(result, 1.0);
}
