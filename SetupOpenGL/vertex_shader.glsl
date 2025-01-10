#version 330 core

in vec3 vertex_position;
in vec2 vertex_texcoord;

out vec2 vs_texcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
//Pass all the values to the fragment shader
	vs_texcoord = vertex_texcoord;

	gl_Position = projection * view * model * vec4(vertex_position, 1.f);
}