#pragma once
#include "Scene.h"
#include "Plane.h"
#include "GLSLProgram.h"
#include "Camera.h"
class SceneRipple : public Scene
{
public:
	SceneRipple();
	// Inherited via Scene
	virtual void init() override;

	virtual void update(float t) override;

	virtual void render() override;

	virtual void resize(int, int) override;

	virtual void onMouseMove(double xpos, double ypos) override;

	virtual void onMouseScroll(double xoffset, double yoffset) override;

	virtual void onMouseButton(int button, int action) override;

	virtual void onKey(int key, int action) override;

	virtual Camera* getCamera() override;

private:
	GLSLProgram prog;
	Plane plane;
	Camera camera;

};

