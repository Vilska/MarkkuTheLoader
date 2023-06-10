#version 330 core

layout(location = 0) out vec4 color;

uniform vec3 LightPos;
uniform vec3 LightColor;
uniform vec3 ViewPos;

in vec3 v_FragPos;
in vec3 v_Normal;

void main()
{
    vec3 ambient = 0.1 * LightColor;

    vec3 norm = normalize(v_Normal);
    vec3 lightDir = normalize(LightPos - v_FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * LightColor;

    vec3 viewDir = normalize(ViewPos - v_FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = 0.5 * spec * LightColor;

    vec3 result = (ambient + diffuse + specular) * vec3(1.0, 0.5, 0.2);
    color = vec4(result, 1.0);
}