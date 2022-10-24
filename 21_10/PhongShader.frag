#version 330
in vec4 worldPos;
in vec3 worldNorm;

uniform vec3 lightPosition;
uniform vec3 viewPosition;

out vec4 frag_color;

void main () {	
	// Light vector
	vec3 lightVector = normalize(lightPosition - vec3(worldPos));
	// View Vector
	vec3 viewVector = normalize(viewPosition - vec3(worldPos));

	// Specular	
	float specularStrength = 0.8;
	float spec = pow(max(dot(viewVector, reflect(-lightVector, worldNorm)), 0.0), 16);
	vec4 specular = specularStrength * spec * vec4( 0.385, 0.647, 0.812, 1.0);
	
	// DIFFUSE
	float dot_product = max(dot(lightVector, worldNorm), 0.0);
	vec4 diffuse = dot_product * vec4( 0.385, 0.647, 0.812, 1.0);

	// Ambient
	vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
	frag_color = ambient + diffuse + specular;

}