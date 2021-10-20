#include "Building.h"

Building::Building()
{
	posX = 0;
	posY = 0;
	posZ = 0;

	sizeX = 0;
	sizeY = 0;
	sizeZ = 0;
}

Building::Building(float px, float py, float pz, float sx, float sy, float sz)
{
	posX = px;
	posY = py + (sy/2);
	posZ = pz;

	sizeX = sx;
	sizeY = sy;
	sizeZ = sz;
}

void Building::Generate()
{

}

void Building::Display()
{

}