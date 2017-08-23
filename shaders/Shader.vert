#version 330 core

layout (location=0) in vec3 aPos;
layout (location=0) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos;

out vec3 vPosition;
out vec3 vNormal;
out vec3 lightPosition;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1);

	vNormal = mat3(transpose(inverse(view * model))) * aNormal;
	vPosition = vec3(view * model * vec4(aPos, 1.f));
	
	lightPosition = vec3(view * vec4(lightPos, 1.f));

}