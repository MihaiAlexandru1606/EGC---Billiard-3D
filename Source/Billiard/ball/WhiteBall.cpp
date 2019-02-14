#include "WhiteBall.h"

WhiteBall::WhiteBall(glm::vec3 positionCenter, float radius):
	Ball(positionCenter, radius, glm::vec3(1))
{
}

WhiteBall::~WhiteBall()
{
}

void WhiteBall::moveBall(glm::vec3 delta)
{
	this->positionCenter += delta;
}
