#version 330 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_TexturePos;

uniform mat4 ViewProjection;
uniform mat4 Transform;

out vec3 v_FragPos;
out vec3 v_Normal;
out vec2 v_TexturePos;

void main()
{
	gl_Position = ViewProjection * Transform * vec4(a_Position, 1.0);
	v_FragPos = vec3(Transform * vec4(a_Position, 1.0));
	v_Normal = a_Normal;
	v_TexturePos = a_TexturePos;
}