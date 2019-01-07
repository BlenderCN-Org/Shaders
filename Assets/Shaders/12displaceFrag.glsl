# version 400 core
uniform sampler2D mainTex;
uniform sampler2D secondTex;
in Vertex {
	vec4 colour;
	vec2 texCoord;
	vec4 pos;
} IN;
out vec4 fragColor;

void main (void) {
	fragColor = texture(mainTex, IN.texCoord);
	fragColor.a = IN.colour.a;
}