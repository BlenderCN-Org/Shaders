#include "../../Common/Window.h"
#include "../../Common/TextureLoader.h"
#include "../../Common/Vector3.h"
#include "../../Common/Vector4.h"
#include "../../Common/MeshGeometry.h"
#include "../../Common/Maths.h"
#include "../../Common/Camera.h"
#include "Cube.h"

#include "../../Plugins/OpenGLRendering/OGLRenderer.h"
#include "../../Plugins/OpenGLRendering/OGLMesh.h"
#include "../../Plugins/OpenGLRendering/OGLShader.h"
#include "../../Plugins/OpenGLRendering/OGLTexture.h"

#include "Renderer.h"


using namespace NCL;
using namespace CSC3223;
Cube* ShrinkCube(Renderer& r);
Cube* BlendCube(Renderer& r);
Cube* FadeCube(Renderer& r);
Cube* FallApartCube(Renderer & renderer);
Cube* ExplodeCube(Renderer & renderer);
Cube* SnowyCube(Renderer& renderer);
void changeCube(Renderer& r);
Cube* currentCube = nullptr;

bool rotate = true;

int main() {
	Window*w = Window::CreateGameWindow("CSC3223 Coursework 2!");

	if (!w->HasInitialised()) {
		return -1;
	}

	Renderer*	renderer = new Renderer(*w);
	Matrix4 projection = Matrix4::Perspective(1.0f, 100.0f, 800.0f / 600.0f, 45.0f);
	renderer->SetProjectionMatrix(projection);

	Camera *c = new Camera();
	
	
	//FallApartCube(*renderer);
	//ShrinkCube(*renderer);
	//BlendCube(*renderer);
	//FadeCube(*renderer);
	//ExplodeCube(*renderer);
	//snowyCube = SnowyCube(*renderer);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	while (w->UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {
		glEnable(GL_BLEND); 
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		float time = w->GetTimer()->GetTimeDelta();
		if (currentCube && rotate) {
			currentCube->SetTransform(currentCube->GetTransform()*Matrix4::Rotation(0.1, Vector3(1, 1, 0)));
		}

		Vector2 mousePos = w->GetMouse()->GetAbsolutePosition();
		Vector2 texCoord = Vector2(mousePos.x / w->GetScreenSize().x, 1- mousePos.y / w->GetScreenSize().y);
		Vector2 oglCoord = Vector2(mousePos.x / (w->GetScreenSize().x/2) -1, (-mousePos.y / (w->GetScreenSize().y/2))+1);
		
		renderer->SetMouseLocation(texCoord);

		renderer->Update(time);

		renderer->Render();
		changeCube(*renderer);
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_PRIOR)) {
			w->ShowConsole(true);
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_NEXT)) {
			w->ShowConsole(false);
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_HOME)) {
			w->SetFullScreen(true);
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_END)) {
			w->SetFullScreen(false);
		}
		if (Window::GetMouse()->ButtonPressed(MouseButtons::MOUSE_LEFT)) {
			renderer->AddFootstep(texCoord.x, texCoord.y);
		}
		void changeCube(Renderer r);

		w->SetTitle(std::to_string(time));
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	delete renderer;

	Window::DestroyGameWindow();
}
void changeCube(Renderer& r) {

	if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::KEYBOARD_1)) {
		rotate = true;
		r.DeleteAllRenderObjects();
		r.resetTimer();
		currentCube = ShrinkCube(r);
	}
	if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::KEYBOARD_2)) {
		rotate = true;
		r.DeleteAllRenderObjects();
		r.resetTimer();
		currentCube = BlendCube(r);
	}
	if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::KEYBOARD_3)) {
		rotate = true;
		r.DeleteAllRenderObjects();
		r.resetTimer();
		currentCube = FadeCube(r);
	}
	if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::KEYBOARD_4)) {
		rotate = false;
		r.DeleteAllRenderObjects();
		r.resetTimer();
		currentCube = FallApartCube(r);
	}
	if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::KEYBOARD_5)) {
		rotate = true;
		r.DeleteAllRenderObjects();
		r.resetTimer();
		currentCube = ExplodeCube(r);
	}
	if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::KEYBOARD_6)) {
		rotate = true;
		r.DeleteAllRenderObjects();
		r.resetTimer();
		currentCube = SnowyCube(r);
	}
}
Cube* ShrinkCube(Renderer& r) {
	Matrix4 transform = Matrix4::Translation(Vector3(0, 0, -20))*Matrix4::Scale(Vector3(5, 5, 5));
	Cube *c = new Cube(transform);
	OGLShader *shrink = new OGLShader("VertexShrink.glsl", "FragmentBasic.glsl");
    c -> SetShader(shrink);
	r.AddRenderObject(c);
	return c;
}
Cube* BlendCube(Renderer& r) {
	Matrix4 transform = Matrix4::Translation(Vector3(0, 0, -20))*Matrix4::Scale(Vector3(5, 5, 5));
	Cube *c = new Cube(transform);
	OGLShader *shrink = new OGLShader("VertexBasic.glsl", "FragmentBlend.glsl");
	c->SetShader(shrink);
	c->SetBaseTexture(OGLTexture::RGBATextureFromFilename("box.png"));
	c->SetSecondTexture(OGLTexture::RGBATextureFromFilename("boxDestroyed.png"));
	r.AddRenderObject(c);
	return c;
}
Cube* FadeCube(Renderer& r) {
	Matrix4 transform = Matrix4::Translation(Vector3(0, 0, -20))*Matrix4::Scale(Vector3(5, 5, 5));
	Cube *c = new Cube(transform);
	OGLShader *shrink = new OGLShader("VertexBasic.glsl", "FragmentFade.glsl");
	c->SetShader(shrink);
	c->SetBaseTexture(OGLTexture::RGBATextureFromFilename("box.png"));
	r.AddRenderObject(c);
	return c;
}
Cube* FallApartCube(Renderer & renderer) {

	Matrix4 transform = Matrix4::Translation(Vector3(0, 0, -40))*Matrix4::Scale(Vector3(5, 5, 5));
	Cube *c = new Cube(transform);
	OGLShader * newShader = new OGLShader(
	"VertexCubes.glsl",
	"FragmentCubes.glsl",
	"GeometryCubes.glsl");
	c->SetShader(newShader);
	c->SetBaseTexture(OGLTexture::RGBATextureFromFilename("box.png"));
	renderer.AddRenderObject(c);
	return c;
}
Cube* ExplodeCube(Renderer & renderer) {	
	Matrix4 transform = Matrix4::Translation(Vector3(0, 0, -20))*Matrix4::Scale(Vector3(4, 4, 4));
	Cube *c = new Cube(transform);
	OGLShader * newShader = new OGLShader("12tessVert.glsl",
		"12displaceFrag.glsl",
		"12Geometry.glsl",
		"12displaceTCS.glsl",
		"12displaceTES.glsl");
	c->SetShader(newShader);
	c->SetBaseTexture(OGLTexture::RGBATextureFromFilename("box.png"));
	c->SetSecondTexture(OGLTexture::RGBATextureFromFilename("boxDestroyed.png"));
	c->Tesselate();
	renderer.AddRenderObject(c);
	return c;
}
Cube* SnowyCube(Renderer & renderer) {
	Matrix4 transform = Matrix4::Translation(Vector3(0, 0, -20))*Matrix4::Scale(Vector3(5, 5, 5));
	Cube *c = new Cube(transform);
	OGLShader * newShader = new OGLShader(
		"footstepVert.glsl",
		"footstepFrag.glsl",
		"",
		"footstepTCS.glsl",
		"footstepTES.glsl");
	c->SetShader(newShader);
	renderer.SetLightProperties(Vector3(0, 15, 0), Vector3(0.9f, 0.95f, 1.0f), 200.0f);

	TextureBase* footstep = OGLTexture::RGBATextureFromFilename("Foot2.png");
	TextureBase* snow = OGLTexture::RGBATextureFromFilename("Snow.png");
	c->SetBaseTexture(snow);
	c->SetSecondTexture(footstep);
	c->Tesselate();
	renderer.AddRenderObject(c);
	return c;
}