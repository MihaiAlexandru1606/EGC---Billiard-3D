#include "Hole.h"


Hole::Hole(glm::vec3 position, float radius):
	position(position), 
	radius(radius)
{
}

Hole::~Hole()
{
}

glm::vec3 Hole::getPosition()
{
	return this->position;
}

float Hole::getRadius()
{
	return radius;
}
