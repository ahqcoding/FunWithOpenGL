#pragma once
#include <GL/glew.h>
#include <string>
class Texture
{
public:
	static GLuint loadTexture(const std::string& name);
	static unsigned char* loadPixels(const std::string& fName, int& w, int& h, bool flip = true);
	static void deletePixels(unsigned char*);

	static GLuint loadCubeMap(const std::string& baseName, const std::string& extention = ".png");
	static GLuint loadHdrCubeMap(const std::string& baseName);
};

