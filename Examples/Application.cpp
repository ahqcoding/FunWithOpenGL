#include "Application.h"

void (*build_framebuffer_callback(Application* a))(GLFWwindow*, int, int)
{
	static Scene* scene = a->getScene();
	void (*callback)(GLFWwindow*, int, int) = ([](GLFWwindow* window, int width, int height) {
		scene->resize(width, height);
	});
	return callback;
}

void (*build_key_callback(Application* a))(GLFWwindow*, int, int, int, int)
{
	static Scene* scene = a->getScene();
	
	void (*callback)(GLFWwindow*, int, int, int, int) = ([](GLFWwindow* window, int key, int scancode, int action, int mods) {
		std::cout << action << std::endl;
		scene->onKey(key, action);
	});
	return callback;
}

void (*build_mouse_callback(Application* a))(GLFWwindow*, double, double)
{
	static Application* app = a;
	void (*callback)(GLFWwindow*, double, double) = ([](GLFWwindow* window, double xpos, double ypos) {
		if (app->firstMouse) {
			app->lastX = xpos;
			app->lastY = ypos;
			app->firstMouse = false;
		}
		float xoffset = xpos - app->lastX;
		float yoffset = app->lastY - ypos;

		app->lastX = xpos;
		app->lastY = ypos;
		app->getScene()->onMouseMove(xoffset, yoffset);
	});
	return callback;
}

void (*build_scroll_callback(Application* a))(GLFWwindow*, double, double)
{
	static Scene* scene = a->getScene();
	void (*callback)(GLFWwindow*, double, double) = ([](GLFWwindow* window, double xoffset, double yoffset) {
		scene->onMouseScroll(xoffset, yoffset);
	});

	return callback;
}

void (*build_mouse_button_callback(Application* a))(GLFWwindow*, int, int, int)
{
	static Scene* scene = a->getScene();
	
	void (*callback)(GLFWwindow*, int, int, int) = ([](GLFWwindow* window, int button, int action, int mods) {
		scene->onMouseButton(button, action);
		});
	return callback;
}

Application::Application(const std::string& title, int width, int height, int samples)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	if (samples > 0) {
		glfwWindowHint(GLFW_SAMPLES, samples);
	}
	mWindow = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, title.c_str(), NULL, NULL);

	if (!mWindow) {
		std::cerr << "Unable to create OpenGL context." << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(mWindow);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
		glfwTerminate();
		
	}


	glfwSetInputMode(mWindow, GLFW_STICKY_KEYS, GLFW_FALSE);
	glfwGetFramebufferSize(mWindow, &fbw, &fbh);

	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	lastX = width / 2.0f;
	lastY = height / 2.0f;
}

void Application::addScene(Scene* s) {
	scene = s;

	glfwSetFramebufferSizeCallback(mWindow, build_framebuffer_callback(this));
	glfwSetCursorPosCallback(mWindow, build_mouse_callback(this));
	glfwSetScrollCallback(mWindow, build_scroll_callback(this));
	glfwSetMouseButtonCallback(mWindow, build_mouse_button_callback(this));
	glfwSetKeyCallback(mWindow, build_key_callback(this));
}

int Application::run() {
	mainLoop();
	glfwTerminate();
	return EXIT_SUCCESS;
}

//void Application::processInput() {	
//	if (glfwGetKey(mWindow, GLFW_KEY_W) == GLFW_PRESS)
//		scene->processKeyboard(GLFW_KEY_W);
//	if (glfwGetKey(mWindow, GLFW_KEY_S) == GLFW_PRESS)
//		scene->processKeyboard(GLFW_KEY_S);
//	if (glfwGetKey(mWindow, GLFW_KEY_A) == GLFW_PRESS)
//		scene->processKeyboard(GLFW_KEY_A);
//	if (glfwGetKey(mWindow, GLFW_KEY_D) == GLFW_PRESS)
//		scene->processKeyboard(GLFW_KEY_D);
//}
void Application::mainLoop() {
	scene->setDimensions(fbw, fbh);
	scene->init();
	scene->resize(fbw, fbh);
	while (!glfwWindowShouldClose(mWindow) && !glfwGetKey(mWindow, GLFW_KEY_ESCAPE)) {
		scene->update(float(glfwGetTime()));
		scene->render();
		glfwSwapBuffers(mWindow);
		glfwPollEvents();
		int state = glfwGetKey(mWindow, GLFW_KEY_SPACE);
		if (state = GLFW_PRESS) {
			scene->animate(!scene->animating());
		}
	}
}
