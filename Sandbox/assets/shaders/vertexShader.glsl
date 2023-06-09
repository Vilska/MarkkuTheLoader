#version 330 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec2 a_TextureCoords;

out vec2 v_TextureCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	v_TextureCoords = a_TextureCoords;
	gl_Position = projection * view * model * vec4(a_Position, 1.0);
}