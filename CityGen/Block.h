#pragma once

#include <vector>
#include "glm/vec3.hpp";

#include "src/Building.h"

class Block {
public:
	glm::vec3 worldPos;
	glm::vec3 size;
	float streetSize;
	std::vector<Building> buildings;
	
	Block();
	Block(glm::vec3 _worldPos);

	void Generate();
	void Display();
};