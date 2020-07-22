#pragma once

#include "TriangleMesh.h"
class Terrain : public TriangleMesh
{
public:
	Terrain(float xsize, float zsize, int xdivs, int zdivs, float smax = 1.0f, float tmax = 1.0f);


};

