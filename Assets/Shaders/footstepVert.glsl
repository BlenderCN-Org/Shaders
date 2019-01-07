#version 400 core

layout(location = 0) in vec3 position;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec3 normal;

uniform  mat4  modelMatrix   = mat4(1.0f);
uniform  mat4  viewMatrix    = mat4(1.0f);
uniform  mat4  projMatrix    = mat4(1.0f);

out Vertex {
	vec2 texCoord;
	vec3 normal;
	vec3 worldPos;
} OUT;

void main(void) {
	vec4 worldPos = modelMatrix * vec4(position , 1.0);
	OUT.worldPos = worldPos.xyz ;

	gl_Position = vec4(position, 1.0);
	OUT.texCoord = texCoord;
	
	mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));

	OUT.normal = normalize(normalMatrix * normalize(normal));
}