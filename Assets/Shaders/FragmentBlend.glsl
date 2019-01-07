#version 400 core
uniform sampler2D mainTex;
uniform sampler2D secondTex;

uniform float time;

in Vertex {
smooth vec4 colour;
smooth vec2 texCoord;
} IN;

out vec4 fragColor;

void main (void) {
	vec4 boxColour = texture(mainTex, IN.texCoord);
	vec4 destroyedColour = texture(secondTex, IN.texCoord);

	
	float destroyTime = 10.0;
		if (time>0.0f && time < destroyTime){
			float step = time/destroyTime*1.5707;
			step = sin(step);
			// -----------------------
			fragColor = mix(boxColour, destroyedColour, step);
		}
		else {
			fragColor = destroyedColour;
		}
}