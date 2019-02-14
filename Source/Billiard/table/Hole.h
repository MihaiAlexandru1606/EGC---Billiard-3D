#pragma once

#include <Core/Engine.h>

class Hole
{
public:
	Hole(glm::vec3 position, float radius);
	~Hole();

	glm::vec3 getPosition();
	float getRadius();

private:

	glm::vec3 position;
	float radius;
};