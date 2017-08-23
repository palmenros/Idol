#version 330 core

uniform vec3 objectColor;
uniform vec3 lightColor;

in vec3 lightPosition;
in vec3 vPosition;
in vec3 vNormal;

out vec4 fragColor;

void main()
{
	vec3 cameraPosition = vec3(0.f, 0.f, 0.f);

	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;

	vec3 normal = normalize(vNormal);
	vec3 lightDir = normalize(lightPosition - vPosition);

	float diffuseStrength = max(dot(normal, lightDir), 0.f);
	vec3 diffuse = diffuseStrength * lightColor;

	vec3 cameraDir = cameraPosition - vPosition;
	float specularStrength = pow(max(dot(reflect(-lightDir, normal), normalize(cameraDir)), 0.f), 32);
	vec3 specular = specularStrength * lightColor;

	vec3 light = ambient + diffuse + specular;
	fragColor = vec4(light * objectColor, 1.f);

}