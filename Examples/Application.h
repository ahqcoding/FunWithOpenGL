#pragma once
#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>

#include "Scene.h"
#include "Camera.h"
#define WIN_WIDTH 800
#define WIN_HEIGHT 600





class Application
{
public:
	Application(const std::string& title, int width = WIN_WIDTH, int height = WIN_HEIGHT, int samples = 0);

	int run();

	void addScene(Scene* scene);
	Scene* getScene() {
		return scene;
	}
	bool firstMouse = true;
	float lastX;
	float lastY;
	// static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	// static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	//static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
private:
	void mainLoop();

	Scene* scene;
	GLFWwindow* mWindow;
	int fbw, fbh;

	
};

