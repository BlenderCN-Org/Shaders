# version 400 core
uniform sampler2D mainTex;
uniform sampler2D secondTex;

uniform vec3 cameraPos;

uniform vec3 lightColour;
uniform vec3 lightPos;
uniform float lightRadius;

in Vertex {
	vec4 colour;
	vec2 texCoord;
    float bFootstep;
	vec2 footstepUvs;
	vec3 normal;
	vec3 worldPos;
} IN;
out vec4 fragColor;

void main (void) {
	vec4 finalColor = vec4(0.0f);
	vec4 footstepColour = vec4(0.0f); 
	footstepColour = texture(secondTex, IN.footstepUvs);
	vec4 snowColour = texture(mainTex, IN.texCoord);
	if (IN.bFootstep>0.99 && footstepColour.r>0.99){
		finalColor = footstepColour;
	}
	else {
		finalColor = snowColour;
	}

	
	vec3 incident	=	normalize(lightPos - IN.worldPos);
	vec3 viewDir	=	normalize(cameraPos - IN.worldPos);
	vec3 halfDir	=	normalize(incident + viewDir);
	
	float dist		= 	length(lightPos - IN.worldPos);
	float atten		=	1.0 - clamp(dist / lightRadius, 0.0, 1.0);
	
	float lambert	=	max(0.0, dot(incident, IN.normal));
	
	float rFactor 	=	max(0.0, dot(halfDir, normalize(IN.normal)));
	float sFactor	=	pow(rFactor, 50.0);
	
	vec4 texCol = finalColor;
	
	vec3 ambient = texCol.rgb * lightColour * 0.1;
	vec3 diffuse = texCol.rgb * lightColour * lambert * atten;
	vec3 specular = lightColour * sFactor * atten/10;
	
	fragColor = vec4(ambient + diffuse + specular , texCol.a);
	
}