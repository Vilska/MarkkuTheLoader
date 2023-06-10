#version 330 core

layout (location = 0) in vec3 a_Position;

uniform mat4 ViewProjection;
uniform mat4 Model;

void main()
{
	gl_Position = ViewProjection * Model * vec4(a_Position, 1.0);
}