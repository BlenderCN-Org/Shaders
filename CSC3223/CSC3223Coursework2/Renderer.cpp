#include "Renderer.h"
#include "../../Common/TextureWriter.h"
#include "../../Common/Maths.h"
#include "../../Common/Matrix3.h"
using namespace NCL;
using namespace Rendering;
using namespace CSC3223;

Renderer::Renderer(Window& w) : OGLRenderer(w)
{
	defaultShader	= new OGLShader("rasterisationVert.glsl", "rasterisationFrag.glsl");
	projMatrix		= Matrix4::Orthographic(-1.0f, 1.0f, (float)currentWidth, 0.0f, 0.0f, (float)currentHeight);
	for (int i = 0; i < 10; i++) {
		footstepLocations[i] = Vector2(-1, -1);
	}
}

Renderer::~Renderer()
{
	delete defaultShader;
}

void NCL::CSC3223::Renderer::EnableBilinearFiltering(OGLTexture & t)
{
	GLuint id = t.GetObjectID();
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);

}

void NCL::CSC3223::Renderer::EnableMipMapFiltering(OGLTexture & t)
{
	GLuint id = t.GetObjectID();
	glBindTexture(GL_TEXTURE_2D, id);
	
	glTexParameteri(GL_TEXTURE_2D,
	GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBindTexture(GL_TEXTURE_2D, 0);
}

void NCL::CSC3223::Renderer::EnableTextureRepeating(OGLTexture & t, bool uRepeat, bool vRepeat)
{
	GLuint id = t.GetObjectID();
	glBindTexture(GL_TEXTURE_2D, id);
	
	 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
	 uRepeat ? GL_REPEAT : GL_CLAMP);
	 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
	 vRepeat ? GL_REPEAT : GL_CLAMP);
	
	 glBindTexture(GL_TEXTURE_2D, 0);
}

void NCL::CSC3223::Renderer::AddFootstep(double x, double y)
{
	if (currentId > 9)
		currentId = 0;
	footstepLocations[currentId] = Vector2(x, y);
	currentId++;
}



void Renderer::RenderFrame() {
	OGLShader* activeShader = nullptr;

	int modelLocation	= 0; 

	for (const RenderObject* object : renderObjects) {
		OGLShader* objectShader = (OGLShader*)object->GetShader();
		if (!object->GetMesh()) {
			continue;
		}
		if (objectShader == nullptr) {
			objectShader = defaultShader;
		}
		if (objectShader != activeShader) {
			activeShader = objectShader;
			BindShader(activeShader);
			int projLocation	= glGetUniformLocation(activeShader->GetProgramID(), "projMatrix");
			int viewLocation	= glGetUniformLocation(activeShader->GetProgramID(), "viewMatrix");
			ApplyLightToShader(activeLight, objectShader);

			Matrix3 rotation = Matrix3(viewMatrix);
			Vector3 invCamPos = viewMatrix.GetPositionVector();

			Vector3 camPos = rotation* -invCamPos;

			glUniform3fv(glGetUniformLocation(activeShader->GetProgramID(), "cameraPos"), 1, (float*)&camPos);

			glUniform2fv(glGetUniformLocation(activeShader->GetProgramID(), "hitLocationBottomLeft"), 1, (float*)&mouseLocation);
			glUniform2fv(glGetUniformLocation(activeShader->GetProgramID(), "footstepLocs"), 10, (float*)&footstepLocations);


			modelLocation		= glGetUniformLocation(activeShader->GetProgramID(), "modelMatrix");	
			
			glUniformMatrix4fv(projLocation, 1, false, (float*)&projMatrix);
			glUniformMatrix4fv(viewLocation, 1, false, (float*)&viewMatrix);

			int timeLocation = glGetUniformLocation(activeShader->GetProgramID(), "time");
			if (timeLocation >= 0) {
				float totalTime = frameTimer.GetTotalTime();
				glUniform1f(timeLocation, totalTime*2);
			}
		}

		Matrix4 mat = object->GetTransform();
		glUniformMatrix4fv(modelLocation, 1, false, (float*)&mat);

		BindTextureToShader(object->GetBaseTexture(), "mainTex", 0);
		BindTextureToShader(object->GetSecondTexture(), "secondTex", 1);
		BindMesh(object->GetMesh());
		DrawBoundMesh();
	}
}

void NCL::CSC3223::Renderer::SetLightProperties(Vector3 pos, Vector3 colour, float radius)
{
	activeLight.position = pos;
	activeLight.colour = colour;
	activeLight.radius = radius;

}

void NCL::CSC3223::Renderer::ApplyLightToShader(const Light & l, const OGLShader * s)
{
	glUniform3fv(glGetUniformLocation(s -> GetProgramID(), "lightColour"), 1, (float *)& l.colour);
	glUniform3fv(glGetUniformLocation(s -> GetProgramID(), "lightPos"), 1, (float *)& l.position);
	glUniform1f(glGetUniformLocation(s->GetProgramID(), "lightRadius"), l.radius);
}

void Renderer::OnWindowResize(int w, int h)	{
	OGLRenderer::OnWindowResize(w, h);
	projMatrix = Matrix4::Orthographic(-1.0f, 1.0f, (float)currentWidth, 0.0f, 0.0f, (float)currentHeight);
}