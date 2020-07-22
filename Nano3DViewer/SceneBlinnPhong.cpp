#include "SceneBlinnPhong.h"
#include "Texture.h"
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW\glfw3.h>
using namespace glm;
SceneBlinnPhong::SceneBlinnPhong()
	: cube(1.0f)
	, camera(glm::fvec3(0.0f,0.0f, 3.0f))
	, tPrev(0.0f)
{

}

void SceneBlinnPhong::init() {
	prog.compileShader("shaders/blinnphong.vert.glsl", "shaders/blinnphong.frag.glsl");
	prog.use();
	glEnable(GL_DEPTH_TEST);

	
	projection = mat4(1.0f);
	angle = glm::radians(90.0f);

	vec4 worldLight = vec4(5.0f, 5.0f, 2.0f, 1.0f);

	prog.setUniform("Light.L", 1.0f, 1.0f, 1.0f);
	prog.setUniform("Light.Position", view * worldLight);
	prog.setUniform("Light.La", 0.4f, 0.4f, 0.4f);
	prog.setUniform("Material.Ks", 0.8f, 0.8f, 0.8f);
	prog.setUniform("Material.Shininess", 100.0f);

	
	/*skyTex = Texture::loadHdrCubeMap("media/texture/cube/pisa-hdr/pisa");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyTex);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyTex);*/
	
	 cubeTex = Texture::loadTexture("media/texture/brick1.jpg");
	 glActiveTexture(GL_TEXTURE0);
	 glBindTexture(GL_TEXTURE_2D, cubeTex);
}

void SceneBlinnPhong::update(float t) {
	// angle += 0.5;
	float deltaT = t - tPrev;
	if (tPrev == 0.0f) deltaT = 0.0f;
	tPrev = t;

	angle +=  deltaT;
	if (angle > glm::two_pi<float>()) angle -= glm::two_pi<float>();

}

void SceneBlinnPhong::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	vec3 cameraPos = vec3(7.0f * cos(angle), 2.0f, 7.0f * sin(angle));
	view = glm::lookAt(cameraPos, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	// view = camera.GetViewMatrix();



	model = mat4(1.0f);
	model = glm::rotate(model, glm::radians(angle), vec3(0.0f, 1.0f, 0.0f));
	//model = glm::rotate(model, glm::radians(-35.0f), vec3(1.0f, 0.0f, 0.0f));
	//model = glm::rotate(model, glm::radians(35.0f), vec3(0.0f, 1.0f, 0.0f));

	setMatrices();

	cube.render();
}

void SceneBlinnPhong::setMatrices()
{
	mat4 mv = view * model;
	prog.setUniform("ModelViewMatrix", mv);
	prog.setUniform("NormalMatrix",
		glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
	prog.setUniform("MVP", projection * mv);
}

Camera* SceneBlinnPhong::getCamera()
{
	return &camera;
}

void SceneBlinnPhong::onKey(int key, int action)
{
	if (key == GLFW_KEY_W) {
		camera.ProcessKeyboard(FORWARD, 0.1);

	}

	if (key == GLFW_KEY_S) {
		camera.ProcessKeyboard(BACKWARD, 0.1);
	}

	if (key == GLFW_KEY_A) {
		camera.ProcessKeyboard(LEFT, 0.1);
	}

	if (key == GLFW_KEY_D) {
		camera.ProcessKeyboard(RIGHT, 0.1);
	}
}

void SceneBlinnPhong::resize(int w, int h)
{
	glViewport(0, 0, w, h);
	width = w;
	height = h;
	projection = glm::perspective(glm::radians(70.0f), (float)w / h, 0.3f, 100.0f);
}


