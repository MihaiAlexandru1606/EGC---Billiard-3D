#include "Ball.h"

#include <iostream>

Ball::Ball(glm::vec3 positionCenter, float radius, glm::vec3 color):
	positionCenter(positionCenter),
	radius(radius),
	color(color),
	v_abs(glm::vec3(0)),
	v_direction(glm::vec3(0)),
	in_hole(false),
	limitY(positionCenter.y - radius)
{
}

Ball::~Ball()
{
}

glm::vec3 Ball::getPositionCenter()
{
	return this->positionCenter;
}

void Ball::setPosition(glm::vec3 newPosotion)
{
	positionCenter = newPosotion;
}

float Ball::getRadius()
{
	return this->radius;
}

glm::vec3 Ball::getColor()
{
	return this->color;
}

glm::vec3 Ball::getSpeed()
{
	glm::vec3 v(this->v_abs.x * this->v_direction.x, this->v_abs.y * this->v_direction.y, this->v_abs.z * this->v_direction.z);

	return v;
}

void Ball::setSpeed(glm::vec3 newSpeed)
{
	this->v_abs = glm::vec3(std::fabsf(newSpeed.x), std::fabsf(newSpeed.y), std::fabsf(newSpeed.z));
	
	if (newSpeed.x > 0) {
		this->v_direction.x = 1.0f;
	}
	else {
		this->v_direction.x = -1.0f;
	}

	if (newSpeed.y >= 0) {
		this->v_direction.y = 1.0f;
	}
	else {
		this->v_direction.y = -1.0f;
	}

	if (newSpeed.z > 0) {
		this->v_direction.z = 1.0f;
	}
	else {
		this->v_direction.z = -1.0f;
	}
}

void Ball::updateBall(glm::vec3 acceleration, float time)
{
	if (v_abs.y != 0.0f) {
		acceleration = glm::vec3(0);
	}

	v_abs.x = glm::max(v_abs.x + acceleration.x * time, 0.0f);
	v_abs.y = glm::max(v_abs.y + acceleration.y * time, 0.0f);
	v_abs.z = glm::max(v_abs.z + acceleration.z * time, 0.0f);
	
	glm::vec3 v(this->v_abs.x * this->v_direction.x, this->v_abs.y * this->v_direction.y, this->v_abs.z * this->v_direction.z);

	positionCenter += v * time;
}

void Ball::addSpeed(glm::vec3 v)
{
	v_aux.push_back(v);
}

void Ball::calcSpeed()
{
	if (v_aux.size() != 0) {
		glm::vec3 v = glm::vec3(0);

		for (glm::vec3 speed : v_aux) {
			v += speed;
		}

		this->setSpeed(v * (1.0f / v_aux.size()));

		v_aux.clear();
	}
}

float Ball::distanceToBall(Ball ball)
{
	float distOx = this->positionCenter.x - ball.positionCenter.x;
	float distOy = this->positionCenter.z - ball.positionCenter.z;

	return std::sqrtf(distOx * distOx + distOy * distOy);
}

bool Ball::isStatic()
{
	if (this->isOut()) {
		return true;
	}

	return (this->v_abs.x == 0.0f && this->v_abs.z == 0.0f);
}

bool Ball::inHole()
{
	return in_hole;
}

void Ball::setInHole(bool in)
{
	this->in_hole = in;
}

bool Ball::isOut()
{
	
	if (limitY >= positionCenter.y) {
		return true;
	}

	if (fabs(positionCenter.x) >= 0.76f) {
		return true;
	}

	if (fabs(positionCenter.z) >= 1.38f) {
		return true;
	}
	
	return false;
}
