#version 400 core
layout(quads, cw) in;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

uniform sampler2D mainTex;
uniform sampler2D secondTex;

uniform vec2 footstepLocs[10];

in Vertex {
	vec2 texCoord;
	vec3 normal;
	vec3 worldPos;
} IN[];

out Vertex {
	vec4 colour;
	vec2 texCoord;
    float bFootstep;
	vec2 footstepUvs;
	vec3 normal;
	vec3 worldPos;
} OUT;

vec3 QuadMixVec3(vec3 a, vec3 b, vec3 c, vec3 d) {
	vec3 p0 = mix(a, c, gl_TessCoord.x);
	vec3 p1 = mix(b, d, gl_TessCoord.x);
	
	return mix(p0, p1, gl_TessCoord.y );
}

vec2 QuadMixVec2(vec2 a, vec2 b, vec2 c, vec2 d ){
	vec2 p0 = mix(a, c, gl_TessCoord.x);
	vec2 p1 = mix(b, d, gl_TessCoord.x);
	
	return mix(p0, p1, gl_TessCoord.y );
}
void main(){
	float footstepSize = 0.1;

	vec3 combinedPos = QuadMixVec3(	gl_in[0].gl_Position.xyz,
									gl_in[1].gl_Position.xyz,
									gl_in[2].gl_Position.xyz,
									gl_in[3].gl_Position.xyz);
	vec2 texCoord =	   QuadMixVec2( IN[0].texCoord,
									IN[1].texCoord,
									IN[2].texCoord,
									IN[3].texCoord); 
	
	OUT.normal = QuadMixVec3(	IN[0].normal,
								IN[1].normal,
								IN[2].normal,
								IN[3].normal);
	OUT.texCoord = texCoord;
	
	OUT.worldPos = (modelMatrix*vec4(combinedPos, 1.0)).xyz;
	gl_Position = vec4(OUT.worldPos, 1.0);

	
	for (int i =0; i<10; i++){
		vec2 hitLocationTopRight = vec2(footstepLocs[i].x+footstepSize, footstepLocs[i].y+footstepSize);
		if (footstepLocs[i].x>=0 && texCoord.x>footstepLocs[i].x && texCoord.y>footstepLocs[i].y 
		&& texCoord.x<hitLocationTopRight.x && texCoord.y<hitLocationTopRight.y){
			float xLen = hitLocationTopRight.x - footstepLocs[i].x;
			float yLen = hitLocationTopRight.y - footstepLocs[i].y;
	
			float dx = texCoord.x - footstepLocs[i].x;
			float dy = texCoord.y - footstepLocs[i].y;
			
			vec2 footstepUvs = vec2(clamp(dx/xLen, 0, 1), clamp(dy/yLen, 0, 1));
			
			OUT.footstepUvs = footstepUvs;
			OUT.bFootstep = 1.0;
			vec4 col = texture(secondTex, footstepUvs);
			if (col.r>0.9){
				gl_Position.xyz-=OUT.normal/5;
			}
			break;
		}
		else {
			OUT.bFootstep = 0.0;
		}
	}

	gl_Position = projMatrix*viewMatrix*gl_Position;
}





