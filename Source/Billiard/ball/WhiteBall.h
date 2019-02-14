#pragma once

#include "Ball.h"

class WhiteBall : public Ball
{
public:
	WhiteBall(glm::vec3 positionCenter, float radius);
	~WhiteBall();

	void moveBall(glm::vec3 delta);

private:

};