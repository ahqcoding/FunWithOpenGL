#pragma once
#include "Scene.h"
#include "GLSLProgram.h"
class ScenePointSprite : public Scene
{
public:
	ScenePointSprite();
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
	GLuint sprites;
	int numSprites;
	float* locations;
};

