#include "SceneSubdivide.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <GLFW/glfw3.h>

using namespace glm;

//projection and modelview matrices
glm::mat4  P = glm::mat4(1);
glm::mat4 MV = glm::mat4(1);

//camera transformation variables
int state = 0, oldX = 0, oldY = 0;
float rX = 25, rY = -40, dist = -35;


SceneSubdivide::SceneSubdivide()
{
}

void SceneSubdivide::init()
{
	glm::vec3 vertices[4];
	GLushort indices[6];
	vertices[0] = glm::vec3(-5, 0, -5);
	vertices[1] = glm::vec3(-5, 0, 5);
	vertices[2] = glm::vec3(5, 0, 5);
	vertices[3] = glm::vec3(5, 0, -5);
	GLushort* id = &indices[0];
	*id++ = 0;
	*id++ = 1;
	*id++ = 2;
	*id++ = 0;
	*id++ = 2;
	*id++ = 3;

	GLuint vboVerticesID, vboIndicesID;
	glGenVertexArrays(1, &vaoID);
	glGenBuffers(1, &vboVerticesID);
	glGenBuffers(1, &vboIndicesID);
	glBindVertexArray(vaoID);
	glBindBuffer(GL_ARRAY_BUFFER, vboVerticesID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndicesID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);
	glBindVertexArray(0);

	prog.compileShader("shaders/subdivide.vert.glsl", "shaders/subdivide.frag.glsl", "shaders/subdivide.geo.glsl");

	prog.use();
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void SceneSubdivide::update(float t)
{

}

void SceneSubdivide::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(vaoID);
	glm::mat4 T = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, dist));
	glm::mat4 Rx = glm::rotate(T, rX, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 MV = glm::rotate(Rx, rY, glm::vec3(0.0f, 1.0f, 0.0f));
	MV = glm::translate(MV, glm::vec3(-5, 0, -5));
	prog.setUniform("sub_divisions", sub_divisions);
	prog.setUniform("MVP", projection * MV);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

	MV = glm::translate(MV, glm::vec3(10, 0, 0));
	prog.setUniform("MVP", projection * MV);
	//draw the second submesh
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

	MV = glm::translate(MV, glm::vec3(0, 0, 10));
	prog.setUniform("MVP", projection * MV);
	//draw the second submesh
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

	MV = glm::translate(MV, glm::vec3(-10, 0, 0));
	prog.setUniform("MVP", projection * MV);
	//draw the second submesh
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}

void SceneSubdivide::resize(int w, int h)
{
	glViewport(0, 0, w, h);
	width = w;
	height = h;
	projection = glm::perspective(glm::radians(70.0f), (float)w / h, 0.3f, 100.0f);
}

void SceneSubdivide::onMouseMove(double xpos, double ypos)
{
}

void SceneSubdivide::onMouseScroll(double xoffset, double yoffset)
{
}

void SceneSubdivide::onMouseButton(int button, int action)
{
}

void SceneSubdivide::onKey(int key, int action)
{

	if (key == GLFW_KEY_W && action == GLFW_PRESS) {

		sub_divisions++;
	}

	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		sub_divisions--;
	}

	sub_divisions = max(1, min(8, sub_divisions));
}

Camera* SceneSubdivide::getCamera()
{
    return nullptr;
}
