#version 400 core
uniform sampler2D mainTex;

uniform float time;

in Vertex {
smooth vec4 colour;
smooth vec2 texCoord;
} IN;

out vec4 fragColor;

void main (void) {

	vec4 boxColour = texture(mainTex, IN.texCoord);
	
	float destroyTime = 10.0;
	
	if (time>0.0f && time < destroyTime)
	{
			float step = time/destroyTime*1.5707;
			step = sin(step);
			// ------------------------------------------------
			vec4 resultColor = vec4(boxColour.rgb, (1.0 - step));
			fragColor = resultColor;
	}
	else 
	{
		vec4 resultColor = vec4(0.0);
		fragColor = resultColor;
	}
}