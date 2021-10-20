#pragma once

#include "glm/vec3.hpp"
#include "of"

class Building {
public:
	float posX;
	float posY;
	float posZ;

	float sizeX;
	float sizeY;
	float sizeZ;

	glm::vec3 pos;
	glm::vec3 size;

	Building();
	Building(float px, float py, float pz, float sx, float sy, float sz);
	Building(glm::vec3 _pos, glm::vec3 _size);

	void Generate();
	void Display();
};