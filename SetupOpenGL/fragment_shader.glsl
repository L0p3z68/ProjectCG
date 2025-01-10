#version 440

in vec2 vs_texcoord;

out vec4 fs_color;

//Uniforms
uniform sampler2D myTexture;


void main()
{
	fs_color = texture(myTexture, vs_texcoord);
}
