#pragma once

#include <Core/Engine.h>

class Tac
{
public:
	Tac();
	~ Tac();

	glm::vec3 getPosition();
	void setPosition(glm::vec3 position);
	glm::vec3 getDimension();
	
	float getAngle(glm::vec3 posotionBall);
	void movetTac();

private:

	glm::vec3 position;
	glm::vec3 dimension;
};