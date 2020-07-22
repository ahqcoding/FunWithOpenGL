#pragma once
#include "Scene.h"
#include "GLSLProgram.h"
#include "Cube.h"
#include "Camera.h"
class SceneBlinnPhong : public Scene
{
public:
	SceneBlinnPhong();

	void init();
	void update(float t);
	void render();
	void resize(int, int);
	void onKey(int, int);
	Camera* getCamera();
private:
	GLSLProgram prog;
	GLuint cubeTex;
	Cube cube;
	float angle;
	float tPrev;
	void setMatrices();
	Camera camera;
	// Inherited via Scene
	
	
};

