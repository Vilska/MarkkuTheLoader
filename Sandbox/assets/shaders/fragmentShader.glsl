#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TextureCoords;

uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;

void main()
{
    color = mix(texture(u_Texture1, v_TextureCoords), texture(u_Texture2, v_TextureCoords), 0.2);
}