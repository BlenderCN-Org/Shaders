#version 400 core

uniform mat4 modelMatrix = mat4(1.0f);
uniform mat4 viewMatrix = mat4(1.0f );
uniform mat4 projMatrix = mat4(1.0f);

uniform float time = 0.0f;
uniform vec3 pivot = vec3(0.0f);

layout ( location = 0) in vec3 position;
layout ( location = 1) in vec4 colour;
layout ( location = 2) in vec2 texCoord;

out Vertex
{
	vec4 colour;
	vec2 texCoord;
} OUT;

void main(void)
{
	float destroyTime = 10.0f;
	float start = 1.57079633;

	mat4 mvp = (projMatrix * viewMatrix * modelMatrix);
	if (time>0.0f && time <destroyTime){
		float step = start + (time/destroyTime)*start;
		step = sin(step);
		gl_Position = mvp * vec4 (vec3(position.x * step, position.y * step, position.z * step), 1.0);
	}
	else 
	{
		gl_Position = mvp*vec4(vec3(0.0), 1.0);
	}
	OUT.texCoord = texCoord;
	OUT.colour = vec4(0.4, 0.5, 0.6, 1.0);
}