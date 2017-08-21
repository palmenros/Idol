#version 330 core

layout (location=0) in vec2 vPos;
layout (location=1) in vec3 vColor;
layout (location=2) in vec2 texCoord;

out vec4 vertexColor;
out vec2 texCoordinates;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(vPos, 0, 1);
	vertexColor = vec4(vColor, 1);
	texCoordinates = texCoord;
}