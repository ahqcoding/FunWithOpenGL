#pragma once
#include "Scene.h"
#include "GLSLProgram.h"
#include "Cube.h"
#include "Camera.h"
#include "Plane.h"
class ScenePBR : public Scene
{
public:
	ScenePBR();
	// Inherited via Scene
	virtual void init() override;
	virtual void update(float t) override;
	virtual void render() override;
	virtual void resize(int, int) override;
	virtual Camera* getCamera() override;
	virtual void onKey(int key, int action) override;

private:
	void setMatrices();
	void drawSpot(const glm::vec3& pos, float rough, int metal, const glm::vec3& color);
	GLSLProgram prog;
	GLuint cubeTex;
	Plane plane;
	Cube cube;
	float angle;
	float tPrev;
	glm::fvec4 lightPos;
	float lightAngle;
	float lightRotationSpeed;
	Camera camera;
};

