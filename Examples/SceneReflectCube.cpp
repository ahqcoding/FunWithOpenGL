#include "SceneReflectCube.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
using glm::vec3;
using glm::mat4;
SceneReflectCube::SceneReflectCube() 
    : angle(0.0f), tPrev(0.0f), rotSpeed(glm::pi<float>() / 8.0f),
      cube(), sky(100.0f)
{

}

void SceneReflectCube::init()
{
    prog.compileShader("shaders/cubemap_reflect.vert.glsl",
        "shaders/cubemap_reflect.frag.glsl");
    skyProg.compileShader("shaders/skybox.vert.glsl",
        "shaders/skybox.frag.glsl");

}

void SceneReflectCube::update(float t)
{
}

void SceneReflectCube::render()
{
}

void SceneReflectCube::resize(int, int)
{
}

Camera* SceneReflectCube::getCamera()
{
    return nullptr;
}

void SceneReflectCube::onKey(int key, int action)
{
}
