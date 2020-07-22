#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
class Camera;
class Scene
{
protected:
    glm::mat4 model, view, projection;

public:
    int width;
    int height;

    Scene() : m_animate(true), width(800), height(600) { }
    virtual ~Scene() {}

    void setDimensions(int w, int h) {
        width = w;
        height = h;
    }

    /**
      Load textures, initialize shaders, etc.
      */
    virtual void init() = 0;

    /**
      This is called prior to every frame.  Use this
      to update your animation.
      */
    virtual void update(float t) = 0;

    /**
      Draw your scene.
      */
    virtual void render() = 0;

    /**
      Called when screen is resized
      */
    virtual void resize(int, int) = 0;
    virtual void onMouseMove(double xpos, double ypos) = 0;
    virtual void onMouseScroll(double xoffset, double yoffset) = 0;
    virtual void onMouseButton(int button, int action) = 0;
    virtual void onKey(int key, int action) = 0;
    virtual Camera* getCamera() = 0;
   

    void animate(bool value) { m_animate = value; }
    bool animating() { return m_animate; }

protected:
    bool m_animate;
};