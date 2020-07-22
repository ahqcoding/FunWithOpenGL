#pragma once

#include "Scene.h"
#include "GLSLProgram.h"
#include "Cube.h"
#include "Camera.h"
#include "Plane.h"
#include "Random.h"
#include "Grid.h"
class SceneParticles : public Scene
{
public:

	SceneParticles();
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
	Random rand;

	GLSLProgram prog, flatProg;
	GLuint initVel, startTime, particles, nParticles;
	Grid grid;
	glm::vec3 emitterPos, emitterDir;

	float angle, time, particleLifeTime;


	

};

