#pragma once

#include "Scene.h"
#include "Terrain.h"
#include "GLSLProgram.h"
#include "Camera.h"
class SceneTerrain : public Scene
{
public:
	SceneTerrain();
	~SceneTerrain();
	// Inherited via Scene
	virtual void init() override;

	virtual void update(float t) override;

	virtual void render() override;

	virtual void resize(int, int) override;

	virtual Camera* getCamera() override;

	virtual void onKey(int key, int action) override;

	virtual void onMouseMove(double xpos, double ypos) override;


	virtual void onMouseScroll(double xoffset, double yoffset) override;

	virtual void onMouseButton(int button, int action) override;

private:
	GLSLProgram prog;
	Terrain terrain;
	Camera camera;



};

