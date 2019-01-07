#pragma once
#include "RenderObject.h"
namespace NCL {
	namespace CSC3223 {
		class Cube : public RenderObject
		{
		public:
			Cube(NCL::Maths::Matrix4 m);
			~Cube();
			void Tesselate();
		};
	}

}


