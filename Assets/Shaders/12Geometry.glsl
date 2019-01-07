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

uniform float particleSize = 0.1;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

uniform sampler2D mainTex;
uniform sampler2D secondTex;

uniform float time;

void main() {
	gl_PrimitiveIDIn;
	
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
	vec4 vertexColor = texture(secondTex, IN[0].texCoord);
	float shaderTime = time-1;
	if (shaderTime>=0) {
	float deltaSide = (sin(shaderTime+1.57079633)+1)*0.5;
	if (shaderTime>=3.14159266) {
		deltaSide = (shaderTime/3.14159266-1);
		deltaSide = deltaSide*50;
	}
	if (shaderTime<=3.14159266){
		for (int i =0; i<36; i+=3){
		vec4 target = vec4(normalize(IN[0].pos.xyz), IN[0].pos.w);
		vec4 usual = IN[0].pos;
		vec4 current = mix(usual, target, deltaSide);
		
		vec4 worldPos = modelMatrix*current;
		worldPos += vec4(vertices[i]*particleSize, 0.0f);
		worldPos.x+=current.x*deltaSide;
		worldPos.y+=current.y*deltaSide;
		worldPos.z+=current.z*deltaSide;
		vec4 viewPos = viewMatrix* worldPos;
		gl_Position = projMatrix * viewPos;
		OUT.colour = vec4(1.0);
		OUT.texCoord = texCoords[i];
		EmitVertex();
		
		
		worldPos = modelMatrix * current;
		worldPos += vec4(vertices[i+1]*particleSize, 0.0f);
		worldPos.x+=current.x*deltaSide;
		worldPos.y+=current.y*deltaSide;
		worldPos.z+=current.z*deltaSide;
		viewPos = viewMatrix* worldPos;
		gl_Position = projMatrix * viewPos;
		OUT.colour = vec4(1.0);
		OUT.texCoord = texCoords[i+1];
		EmitVertex();
		
		worldPos = modelMatrix * current;
		worldPos += vec4(vertices[i+2]*particleSize, 0.0f);
		worldPos.x+=current.x*deltaSide;
		worldPos.y+=current.y*deltaSide;
		worldPos.z+=current.z*deltaSide;
		viewPos = viewMatrix* worldPos;
		gl_Position = projMatrix * viewPos;
		OUT.colour = vec4(1.0);
		OUT.texCoord = texCoords[i+2];
		EmitVertex();

		EndPrimitive();
		}
	}
	else {
		if(vertexColor.a<=0.1){
				for (int i =0; i<36; i+=3){
				vec4 current = IN[0].pos;
				
				vec4 worldPos = modelMatrix*current;
				worldPos += vec4(vertices[i]*particleSize, 0.0f);
				worldPos.x+=current.x*deltaSide;
				worldPos.y+=current.y*deltaSide;
				worldPos.z+=current.z*deltaSide;
				vec4 viewPos = viewMatrix* worldPos;
				gl_Position = projMatrix * viewPos;
				OUT.colour = vec4(1.0);
				OUT.texCoord = texCoords[i];
				EmitVertex();
				
				
				worldPos = modelMatrix * current;
				worldPos += vec4(vertices[i+1]*particleSize, 0.0f);
				worldPos.x+=current.x*deltaSide;
				worldPos.y+=current.y*deltaSide;
				worldPos.z+=current.z*deltaSide;
				viewPos = viewMatrix* worldPos;
				gl_Position = projMatrix * viewPos;
				OUT.colour = vec4(1.0);
				OUT.texCoord = texCoords[i+1];
				EmitVertex();
				
				worldPos = modelMatrix * current;
				worldPos += vec4(vertices[i+2]*particleSize, 0.0f);
				worldPos.x+=current.x*deltaSide;
				worldPos.y+=current.y*deltaSide;
				worldPos.z+=current.z*deltaSide;
				viewPos = viewMatrix* worldPos;
				gl_Position = projMatrix * viewPos;
				OUT.colour = vec4(1.0);
				OUT.texCoord = texCoords[i+2];
				EmitVertex();
		
				EndPrimitive();
				}
			}
			else {
				deltaSide=0;
				for (int i =0; i<36; i+=3){
				vec4 current = IN[0].pos;
				
				vec4 worldPos = modelMatrix*current;
				worldPos += vec4(vertices[i]*particleSize, 0.0f);
				worldPos.x+=current.x*deltaSide;
				worldPos.y+=current.y*deltaSide;
				worldPos.z+=current.z*deltaSide;
				vec4 viewPos = viewMatrix* worldPos;
				gl_Position = projMatrix * viewPos;
				OUT.colour = vec4(1.0);
				OUT.texCoord = texCoords[i];
				EmitVertex();
				
				
				worldPos = modelMatrix * current;
				worldPos += vec4(vertices[i+1]*particleSize, 0.0f);
				worldPos.x+=current.x*deltaSide;
				worldPos.y+=current.y*deltaSide;
				worldPos.z+=current.z*deltaSide;
				viewPos = viewMatrix* worldPos;
				gl_Position = projMatrix * viewPos;
				OUT.colour = vec4(1.0);
				OUT.texCoord = texCoords[i+1];
				EmitVertex();
				
				worldPos = modelMatrix * current;
				worldPos += vec4(vertices[i+2]*particleSize, 0.0f);
				worldPos.x+=current.x*deltaSide;
				worldPos.y+=current.y*deltaSide;
				worldPos.z+=current.z*deltaSide;
				viewPos = viewMatrix* worldPos;
				gl_Position = projMatrix * viewPos;
				OUT.colour = vec4(1.0);
				OUT.texCoord = texCoords[i+2];
				EmitVertex();
		
				EndPrimitive();
				}
			}
		}

	}
	
	}