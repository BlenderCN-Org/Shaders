# version 400 core
layout (vertices =4) out ; // num vertices in output patch

in Vertex {
	vec2 texCoord;
	vec3 normal;
	vec3 worldPos;
} IN []; // Equal to size of the draw call vertex count

out Vertex {
	vec2 texCoord;
	vec3 normal;
	vec3 worldPos;
 // To Evaluation Shader
} OUT []; // Equal to the size of the layout vertex count

void main () {
	gl_TessLevelInner [0] = 512*8;
	gl_TessLevelInner [1] = 512*8;
	gl_TessLevelOuter [0] = 512*8;
	gl_TessLevelOuter [1] = 512*8;
	gl_TessLevelOuter [2] = 512*8;
	gl_TessLevelOuter [3] = 512*8;
	
	OUT[gl_InvocationID].texCoord = IN[gl_InvocationID].texCoord;
	OUT[gl_InvocationID].normal = IN[gl_InvocationID].normal;
	gl_out[gl_InvocationID].gl_Position =
	gl_in[gl_InvocationID].gl_Position;
}
