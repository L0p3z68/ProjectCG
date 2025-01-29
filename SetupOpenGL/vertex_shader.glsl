#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textCoord;

out vec2 TexCoords;

uniform mat4 model;
uniform mat2 texCoordStart;
uniform mat2 texCoordEnd;

void main()
{
    TexCoords = mix(texCoordStart, texCoordEnd, texCoord);
    gl_Position = projection * vec4(position, 1.0);
}