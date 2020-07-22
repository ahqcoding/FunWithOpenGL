#pragma once
#include "Scene.h"
#include "GLSLProgram.h"
#include "Cube.h"
#include "Camera.h"
#include "SkyBox.h"
class SceneReflectCube : public Scene
{
public:
	SceneReflectCube();

	// Inherited via Scene
	virtual void init() override;

	virtual void update(float t) override;

	virtual void render() override;

	virtual void resize(int, int) override;

	virtual Camera* getCamera() override;

	virtual void onKey(int key, int action) override;

private:
	void setMatrices();


	GLSLProgram prog, skyProg;
	GLuint cubeTex;
	SkyBox sky;
	Cube cube;
	float angle, tPrev, rotSpeed;
	
	Camera camera;
	// Inherited via Scene
};

