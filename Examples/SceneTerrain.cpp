#include "SceneTerrain.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

using namespace glm;
SceneTerrain::SceneTerrain() 
    :terrain(100, 100, 100, 100)
	,camera(glm::vec3(3.0f, 10.0f, 10.0f))
{

}

SceneTerrain::~SceneTerrain()
{
	
}

void SceneTerrain::init()
{
    prog.compileShader("shaders/terrain.vert.glsl", "shaders/terrain.frag.glsl");

	prog.use();
	glEnable(GL_DEPTH_TEST);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	projection = mat4(1.0f);
	
	view = camera.GetViewMatrix();
	// view = glm::lookAt(vec3(3.0,10.f, 10.f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	model = mat4(1.0f);
	vec4 worldLight = vec4(4.0f, 4.0f, 30.0f, 1.0f);

	prog.setUniform("Light.L", 0.8f, 0.8f, 0.8f);
	prog.setUniform("Light.Position", view * worldLight);
	prog.setUniform("Light.La", 0.4f, 0.4f, 0.4f);
	
}

void SceneTerrain::update(float t)
{
}

void SceneTerrain::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	mat4 mv = view * model;
	prog.setUniform("ModelViewMatrix", mv);
	prog.setUniform("NormalMatrix",
		glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
	prog.setUniform("MVP", projection * mv);

	terrain.render();
}

void SceneTerrain::resize(int w, int h)
{
	glViewport(0, 0, w, h);
	width = w;
	height = h;
	projection = glm::perspective(glm::radians(70.0f), (float)w / h, 0.3f, 100.0f);
}

Camera* SceneTerrain::getCamera()
{
    return nullptr;
}

void SceneTerrain::onKey(int key, int action)
{
	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		std::cout << "forward" << std::endl;
		camera.ProcessKeyboard(FORWARD, 0.1);
	}

	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		camera.ProcessKeyboard(BACKWARD, 0.1);
	}

	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		camera.ProcessKeyboard(LEFT, 0.1);
	}

	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		camera.ProcessKeyboard(RIGHT, 0.1);
	}
	view = camera.GetViewMatrix();
}

void SceneTerrain::onMouseMove(double xpos, double ypos)
{
	std::cout << xpos << " " << ypos << std::endl;
	camera.ProcessMouseMovement(xpos, ypos);
	view = camera.GetViewMatrix();
}

void SceneTerrain::onMouseScroll(double xoffset, double yoffset)
{
}

void SceneTerrain::onMouseButton(int button, int action)
{
}
