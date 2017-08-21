#version 330 core

in vec2 texCoordinates;
in vec4 vertexColor;
out vec4 fragColor;

uniform sampler2D container;
uniform sampler2D face;

uniform float alpha;

void main()
{
	vec4 cColor = texture(container, texCoordinates);
	vec4 fColor = texture(face, vec2(texCoordinates.x, 1-texCoordinates.y));
	fragColor = mix(cColor, fColor, alpha);
}