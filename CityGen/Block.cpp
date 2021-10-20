#include "Block.h"

Block::Block()
{
}

Block::Block(glm::vec3 _worldPos)
{

}

void Block::Generate()
{
	
}

void Block::Display()
{
	for (auto building : buildings)
	{
		building.Display();
	}
}


