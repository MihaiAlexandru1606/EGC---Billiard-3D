#pragma once

#include <vector>

#include <Billiard/table/BilliardTable.h>
#include <Billiard/ball/Ball.h>

namespace Collision {
	void setCenter(Ball &ball1, Ball &ball2, float distanceBetween, glm::vec3 normal);

	bool collisionBallBall(Ball &ball1, Ball &ball2);

	bool collisionBallManta(Ball &ball, BilliardTable &billiardTable);

	bool collisoinBallHole(Ball &ball, BilliardTable &billiardTable);

	void collisionBall(WhiteBall &whiteBall, Ball &blackBall, std::vector<Ball> &redBall, std::vector<Ball> &yellowBall);
}