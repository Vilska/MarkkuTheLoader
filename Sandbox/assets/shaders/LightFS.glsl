#version 330 core

layout(location = 0) out vec4 color;

uniform vec3 CubeColor;

void main()
{
    color = vec4(CubeColor, 1.0);
}