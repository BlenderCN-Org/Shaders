#version 400 core
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in Vertex {
	vec4 colour;
	vec2 texCoord;
	vec4 pos;
} IN[];

out Vertex {
	vec4 colour;
	vec2 texCoord;
	vec4 pos;
} OUT;

uniform float particleSize = 4;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

uniform float time;

void main() {
	mat4 mv = viewMatrix*modelMatrix;
	mat4 vp = projMatrix*viewMatrix;
	const vec2 texCoords[36] = vec2[36](
		vec2(0, 0),
		vec2(0, 1),
		vec2(1, 0),

		vec2(1, 0),
		vec2(1, 1),
		vec2(0, 1),

		vec2(0, 0),
		vec2(0, 1),
		vec2(1, 1),

		vec2(1, 1),
		vec2(1, 0),
		vec2(0, 0),

		vec2(0, 0),
		vec2(0, 1),
		vec2(1, 1),

		vec2(1, 1),
		vec2(1, 0),
		vec2(0, 0),

		vec2(0, 0),
		vec2(0, 1),
		vec2(1, 0),

		vec2(1, 0),
		vec2(1, 1),
		vec2(0, 1),

		vec2(0, 1),
		vec2(0, 0),
		vec2(1, 0),

		vec2(1, 0),
		vec2(1, 1),
		vec2(0, 1),

		vec2(0, 1),
		vec2(0, 0),
		vec2(1, 0),

		vec2(1, 0),
		vec2(1, 1),
		vec2(0, 1)
	);
	const vec3 vertices[36] = vec3[36](
		vec3(-1, -1, -1),
		vec3(-1, 1, -1),
		vec3(1, -1, -1),

		vec3(1, -1, -1),
		vec3(1, 1, -1),
		vec3(-1, 1, -1),

		vec3(1, -1, -1),
		vec3(1, 1, -1),
		vec3(1, 1, 1),

		vec3(1, 1, 1),
		vec3(1, -1, 1),
		vec3(1, -1, -1),

		vec3(-1, -1, -1),
		vec3(-1, 1, -1),
		vec3(-1, 1, 1),

		vec3(-1, 1, 1),
		vec3(-1, -1, 1),
		vec3(-1, -1, -1),

		vec3(-1, -1, 1),
		vec3(-1, 1, 1),
		vec3(1, -1, 1),

		vec3(1, -1, 1),
		vec3(1, 1, 1),
		vec3(-1, 1, 1),

		vec3(-1, 1, -1),
		vec3(-1, 1, 1),
		vec3(1, 1, 1),

		vec3(1, 1, 1),
		vec3(1, 1, -1),
		vec3(-1, 1, -1),

		vec3(-1, -1, -1),
		vec3(-1, -1, 1),
		vec3(1, -1, 1),

		vec3(1, -1, 1),
		vec3(1, -1, -1),
		vec3(-1, -1, -1)
	);
	float deltaSide = 0;
	float deltaDown = 0;
	
	if (time>0){
		deltaSide = time;
		deltaDown = -(time*2);
	}
	for (int i =0; i<36; i+=3){
		vec4 worldPos = modelMatrix * IN[0].pos;
		worldPos += vec4(vertices[i]*particleSize, 0.0f);
		worldPos.x+=IN[0].pos.x*deltaSide;
		worldPos.y+=deltaDown;
		worldPos.z+=IN[0].pos.z*deltaSide;
		vec4 viewPos = viewMatrix* worldPos;
		gl_Position = projMatrix * viewPos;
		OUT.colour = vec4(1.0);
		OUT.texCoord = texCoords[i];
		EmitVertex();
		
		worldPos = modelMatrix * IN[0].pos;
		worldPos += vec4(vertices[i+1]*particleSize, 0.0f);
		worldPos.x+=IN[0].pos.x*deltaSide;
		worldPos.y+=deltaDown;
		worldPos.z+=IN[0].pos.z*deltaSide;
		viewPos = viewMatrix* worldPos;
		gl_Position = projMatrix * viewPos;
		OUT.colour = vec4(1.0);
		OUT.texCoord = texCoords[i+1];
		EmitVertex();
		
		worldPos = modelMatrix * IN[0].pos;
		worldPos += vec4(vertices[i+2]*particleSize, 0.0f);
		worldPos.x+=IN[0].pos.x*deltaSide;
		worldPos.y+=deltaDown;
		worldPos.z+=IN[0].pos.z*deltaSide;
		viewPos = viewMatrix* worldPos;
		gl_Position = projMatrix * viewPos;
		OUT.colour = vec4(1.0);
		OUT.texCoord = texCoords[i+2];
		EmitVertex();

		EndPrimitive();
	}
}