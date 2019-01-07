#pragma once
#include "../../Plugins/OpenGLRendering/OGLRenderer.h"
#include "../../Plugins/OpenGLRendering/OGLShader.h"
#include "../../Plugins/OpenGLRendering/OGLTexture.h"
#include "../../Plugins/OpenGLRendering/OGLMesh.h"

#include "RenderObject.h"
#include "../../Common/Vector2.h"

namespace NCL {
	namespace CSC3223 {
		class Renderer : public OGLRenderer
		{
		public:
			struct Light {
				Vector3	position;
				float	radius;
				Vector3	colour;
			};
			Renderer(Window& w);
			~Renderer();

			void AddRenderObject(RenderObject* ro) {
				renderObjects.emplace_back(ro);
			}
			void EnableBilinearFiltering(OGLTexture & t);
			void EnableMipMapFiltering(OGLTexture & t);
			void EnableTextureRepeating(OGLTexture &t, bool uRepeat, bool vRepeat);
			void AddFootstep(double x, double y);
			void DeleteAllRenderObjects() {
				for (const RenderObject* object : renderObjects) {
					delete object;
				}
				renderObjects.clear();
			}
			
			void SetProjectionMatrix(const Matrix4&m) {
				projMatrix = m;
			}
			void SetLightProperties(Vector3 pos, Vector3 colour, float radius);
			void SetViewMatrix(const Matrix4&m) {
				viewMatrix = m;
			}
			void SetMouseLocation(Vector2 loc) {
				mouseLocation = loc;
			}
			void resetTimer() {
				frameTimer.ResetTimer();
			}
		protected:
			Vector2 mouseLocation;

			int currentId = 0;
			Vector2 footstepLocations[10];

			void ApplyLightToShader(const Light& l, const OGLShader* s);
			Light activeLight;
			void RenderNode(RenderObject* root);
			GameTimer frameTimer;
			void OnWindowResize(int w, int h)	override;

			void RenderFrame()	override;
			OGLShader*		defaultShader;

			Matrix4		projMatrix;
			Matrix4		viewMatrix;

			vector<RenderObject*> renderObjects;
		};
	}
}

