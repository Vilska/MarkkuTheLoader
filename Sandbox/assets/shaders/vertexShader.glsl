#version 330 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec2 a_TextureCoords;

out vec2 v_TextureCoords;

uniform mat4 Model;
uniform mat4 ViewProjection;

void main()
{
	v_TextureCoords = a_TextureCoords;
	gl_Position = ViewProjection * Model * vec4(a_Position, 1.0);
}