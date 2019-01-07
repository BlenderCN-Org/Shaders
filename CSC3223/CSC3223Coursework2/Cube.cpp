#include "Cube.h"
#include "../../Common/MeshGeometry.h"
#include <OGLMesh.h>
#include <OGLShader.h>
#include "../../Common/Vector2.h"
using namespace NCL::CSC3223;



Cube::Cube(NCL::Maths::Matrix4 m) : RenderObject(nullptr, m)
{
	std::vector<Vector3> positions = {
		// 1st back
		Vector3(-1, -1, -1),
		Vector3(-1, 1, -1),
		Vector3(1, -1, -1),
		// 2nd back
		Vector3(1, -1, -1),
		Vector3(1, 1, -1),
		Vector3(-1, 1, -1),
		// 1st right
		Vector3(1, -1, -1),
		Vector3(1, 1, -1),
		Vector3(1, 1, 1),
		// 2nd right
		Vector3(1, 1, 1),
		Vector3(1, -1, 1),
		Vector3(1, -1, -1),
		// 1st left
		Vector3(-1, -1, -1),
		Vector3(-1, 1, -1),
		Vector3(-1, 1, 1),
		// 2nd left
		Vector3(-1, 1, 1),
		Vector3(-1, -1, 1),
		Vector3(-1, -1, -1),
		// 1st front
		Vector3(-1, -1, 1),
		Vector3(-1, 1, 1),
		Vector3(1, -1, 1),
		// 2nd front
		Vector3(1, -1, 1),
		Vector3(1, 1, 1),
		Vector3(-1, 1, 1),
		// 1st top
		Vector3(-1, 1, -1),
		Vector3(-1, 1, 1),
		Vector3(1, 1, 1),
		// 2nd top
		Vector3(1, 1, 1),
		Vector3(1, 1, -1),
		Vector3(-1, 1, -1),
		// 1st bottom
		Vector3(-1, -1, -1),
		Vector3(-1, -1, 1),
		Vector3(1, -1, 1),
		// 2nd bottom
		Vector3(1, -1, 1),
		Vector3(1, -1, -1),
		Vector3(-1, -1, -1)
	};
	std::vector<Vector2> texCoords = {
		// 1st back
		Vector2(0, 0),
		Vector2(0, 1),
		Vector2(1, 0),
		// 2nd back
		Vector2(1, 0),
		Vector2(1, 1),
		Vector2(0, 1),
		// 1st right
		Vector2(0, 0),
		Vector2(0, 1),
		Vector2(1, 1),
		// 2nd right
		Vector2(1, 1),
		Vector2(1, 0),
		Vector2(0, 0),
		// 1st left
		Vector2(0, 0),
		Vector2(0, 1),
		Vector2(1, 1),
		// 2nd left
		Vector2(1, 1),
		Vector2(1, 0),
		Vector2(0, 0),
		// 1st front
		Vector2(0, 0),
		Vector2(0, 1),
		Vector2(1, 0),
		// 2nd front
		Vector2(1, 0),
		Vector2(1, 1),
		Vector2(0, 1),
		// 1st top
		Vector2(0, 1),
		Vector2(0, 0),
		Vector2(1, 0),
		// 2nd top
		Vector2(1, 0),
		Vector2(1, 1),
		Vector2(0, 1),
		// 1st bottom
		Vector2(0, 1),
		Vector2(0, 0),
		Vector2(1, 0),
		// 2nd bottom
		Vector2(1, 0),
		Vector2(1, 1),
		Vector2(0, 1),
	};
	OGLMesh *cubeMesh = new OGLMesh();
	mesh = cubeMesh;
	cubeMesh->SetVertexPositions(positions);
	cubeMesh->SetVertexTextureCoords(texCoords);
	cubeMesh->SetPrimitiveType(GeometryPrimitive::Triangles);
	cubeMesh->UploadToGPU();

	SetTransform(m);
}
Cube::~Cube()
{

}

void NCL::CSC3223::Cube::Tesselate()
{

	std::vector<Vector3> positions = {
		// front
		Vector3(-1, -1, 1),
		Vector3(-1, 1, 1),
		Vector3(1, -1, 1),
		Vector3(1, 1, 1),
		// back
		Vector3(-1, -1, -1),
		Vector3(-1, 1, -1),
		Vector3(1, -1, -1),
		Vector3(1, 1, -1),
		// right
		Vector3(1, -1, 1),
		Vector3(1, 1, 1),
		Vector3(1, -1, -1),
		Vector3(1, 1, -1),
		// left
		Vector3(-1, -1, 1),
		Vector3(-1, 1, 1),
		Vector3(-1, -1, -1),
		Vector3(-1, 1, -1),
		// bottom
		Vector3(-1, -1, 1),
		Vector3(-1, -1, -1),
		Vector3(1, -1, 1),
		Vector3(1, -1, -1),
		// top
		Vector3(-1, 1, 1),
		Vector3(-1, 1, -1),
		Vector3(1, 1, 1),
		Vector3(1, 1, -1)
	};
	std::vector<Vector3> normals = {
		// front
		Vector3(-1, -1, 1),
		Vector3(-1, 1, 1),
		Vector3(1, -1, 1),
		Vector3(1, 1, 1),
		// back
		Vector3(-1, -1, -1),
		Vector3(-1, 1, -1),
		Vector3(1, -1, -1),
		Vector3(1, 1, -1),
		// right
		Vector3(1, -1, 1),
		Vector3(1, 1, 1),
		Vector3(1, -1, -1),
		Vector3(1, 1, -1),
		// left
		Vector3(-1, -1, 1),
		Vector3(-1, 1, 1),
		Vector3(-1, -1, -1),
		Vector3(-1, 1, -1),
		// bottom
		Vector3(-1, -1, 1),
		Vector3(-1, -1, -1),
		Vector3(1, -1, 1),
		Vector3(1, -1, -1),
		// top
		Vector3(-1, 1, 1),
		Vector3(-1, 1, -1),
		Vector3(1, 1, 1),
		Vector3(1, 1, -1)
	};
	std::vector<Vector2> texCoords = {
		// front
		Vector2(0, 0),
		Vector2(0, 1),
		Vector2(1, 0),
		Vector2(1, 1),
		// back
		Vector2(0, 0),
		Vector2(0, 1),
		Vector2(1, 0),
		Vector2(1, 1),
		// right
		Vector2(0, 0),
		Vector2(0, 1),
		Vector2(1, 0),
		Vector2(1, 1),
		// left
		Vector2(0, 0),
		Vector2(0, 1),
		Vector2(1, 0),
		Vector2(1, 1),
		// bottom
		Vector2(0, 0),
		Vector2(0, 1),
		Vector2(1, 0),
		Vector2(1, 1),
		// top
		Vector2(0, 0),
		Vector2(0, 1),
		Vector2(1, 0),
		Vector2(1, 1)
	};


	OGLMesh *cubeMesh = new OGLMesh();
	delete mesh;
	mesh = cubeMesh;
	cubeMesh->SetVertexPositions(positions);
	cubeMesh->SetVertexTextureCoords(texCoords);

	cubeMesh->SetVertexNormals(normals);

	cubeMesh->SetPrimitiveType(GeometryPrimitive::Patches);
	glPatchParameteri(GL_PATCH_VERTICES, 4);
	cubeMesh->UploadToGPU();

	SetTransform(transform);
}

