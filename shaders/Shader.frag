#version 330 core

in vec2 TexCoord;

out vec4 fragColor;

uniform sampler2D container;
uniform sampler2D face;

void main()
{
	vec4 cColor = texture(container, TexCoord);
	vec4 fColor = texture(face, vec2(TexCoord.x, 1 - TexCoord.y));
	fragColor = mix(cColor, fColor, 0.2);
}