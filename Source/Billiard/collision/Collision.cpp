#include "Collision.h"
#include <iostream>

bool Collision::collisionBallBall(Ball & ball1, Ball & ball2)
{
	if (ball1.inHole() || ball2.inHole()) {
		return false;
	}

	bool coll = false;

	glm::vec3 v1 = ball1.getSpeed();
	glm::vec3 v2 = ball2.getSpeed();
	float distX = ball2.getPositionCenter().x - ball1.getPositionCenter().x;
	float distZ = ball2.getPositionCenter().z - ball1.getPositionCenter().z;
	float distance = std::sqrt(distX * distX + distZ * distZ);
	float diameter = 2 * ball1.getRadius();

	glm::vec3 n(distX / distance, 0, distZ / distance);

	
	if (diameter >= distance && (v1 != glm::vec3(0) || v2 != glm::vec3(0))) {
		float p = glm::dot(v1, n) - glm::dot(v2, n);
		glm::vec3 v1_rez = v1 - p * n;
		glm::vec3 v2_rez = v2 + p * n;

		ball1.addSpeed(v1_rez);
		ball2.addSpeed(v2_rez);
	}

	setCenter(ball1, ball2, distance, n);

	return coll;
}

bool Collision::collisionBallManta(Ball & ball, BilliardTable & billiardTable)
{
	if (ball.inHole()) {
		return false;
	}

	glm::vec3 currentPosition = ball.getPositionCenter();
	float ballRadius = ball.getRadius();

	// fata, spate
	if (std::fabs(currentPosition.z) + ballRadius >= billiardTable.getOzLimit()) {
		glm::vec3 newSpeed = ball.getSpeed();
		newSpeed.z = -newSpeed.z;
		
		if(currentPosition.z > 0){
			currentPosition.z = billiardTable.getOzLimit() - ballRadius;
		}
		else{
			currentPosition.z = -(billiardTable.getOzLimit() - ballRadius);
		}

		ball.setPosition(currentPosition);
		ball.setSpeed(newSpeed);

		return true;
	}

	// lateral 
	if (std::fabs(currentPosition.x) + ballRadius >= billiardTable.getOxLimit()) {
		glm::vec3 newSpeed = ball.getSpeed();
		newSpeed.x = -newSpeed.x;

		if (currentPosition.x > 0) {
			currentPosition.x = billiardTable.getOxLimit() - ballRadius;
		}
		else {
			currentPosition.x = -(billiardTable.getOxLimit() - ballRadius);
		}

		ball.setPosition(currentPosition);
		ball.setSpeed(newSpeed);

		return true;
	}

	return false;
}

bool Collision::collisoinBallHole(Ball & ball, BilliardTable & billiardTable)
{
	if (ball.inHole())
		return false;

	float positionX = ball.getPositionCenter().x;
	float positionZ = ball.getPositionCenter().z;

	for (Hole hole : billiardTable.getHoles()) {
		float distX = hole.getPosition().x - positionX;
		float distZ = hole.getPosition().z - positionZ;
		float dist = distX * distX + distZ * distZ;

		if (dist <= hole.getRadius() * hole.getRadius()) {
			ball.setInHole(true);
			glm::vec3 newSpeed = ball.getSpeed() + glm::vec3(0, -2.0f, 0);
			ball.setSpeed(newSpeed);

			return true;
		}
	}

	return false;
}

void Collision::setCenter(Ball & ball1, Ball & ball2, float distanceBetween, glm::vec3 normal)
{
	float d = distanceBetween - 2 * ball1.getRadius();

	if (d < 0) {

		ball1.setPosition(ball1.getPositionCenter() + (d / 2) * normal);
		ball2.setPosition(ball2.getPositionCenter() - (d / 2) * normal);
	}
}
