#pragma once
#include <glm/glm.hpp>
#include <vector>
class HeightMap 
{
public:

	HeightMap(float width, float height, int rows, int cols);

	std::vector<std::vector<glm::vec3>> vertices;
	std::vector<std::vector<glm::vec2>> texCoords;
	std::vector<std::vector<glm::vec3>> normals;
	std::vector<glm::ivec3> indexs;
};

