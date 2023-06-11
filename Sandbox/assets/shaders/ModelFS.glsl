#version 330 core

layout(location = 0) out vec4 color;

struct Material
{
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    float shininess;
};
uniform Material material;

struct Light
{
    vec3 position;
    vec3 color;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;

uniform vec3 ViewPos;
uniform bool NonTexture;

in vec3 v_FragPos;
in vec3 v_Normal;
in vec2 v_TexturePos;

void main()
{
    vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse1, v_TexturePos));

    vec3 norm = normalize(v_Normal);
    vec3 lightDir = normalize(light.position - v_FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse1, v_TexturePos));

    vec3 viewDir = normalize(ViewPos - v_FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.texture_specular1, v_TexturePos));

    vec3 result = light.color * (ambient + diffuse + specular);

    if (!NonTexture)
    {
        color = vec4(result, 1.0);
    }
    else
    {
        color = vec4(0.7, 0.7, 0.7, 1.0);
    }
}