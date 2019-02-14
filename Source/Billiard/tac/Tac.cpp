#include "Tac.h"

Tac::Tac()
{
	this->dimension = glm::vec3(0.01f, 0.01f, 1);
}

Tac::~Tac()
{
}

glm::vec3 Tac::getPosition()
{
	return this->position;
}

void Tac::setPosition(glm::vec3 position)
{
	this->position = position;
}

glm::vec3 Tac::getDimension()
{
	return this->dimension;
}

float Tac::getAngle(glm::vec3 posotionBall)
{
	float deltaX = std::fabs(this->position.x - posotionBall.x);
	float deltaZ = std::fabs(this->position.z - posotionBall.z);


	return std::atan(deltaX / deltaZ);
}
