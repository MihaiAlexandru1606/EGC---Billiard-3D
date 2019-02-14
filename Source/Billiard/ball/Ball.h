#pragma once

#include <string>


#include <Core/Engine.h>

class Ball
{
public:
	Ball(glm::vec3 positionCenter, float radius, glm::vec3 color);
	~Ball();

	glm::vec3 getPositionCenter();
	void setPosition(glm::vec3 newPosotion);
	float getRadius();
	glm::vec3 getColor();

	glm::vec3 getSpeed();
	void setSpeed(glm::vec3 newSpeed);
	void updateBall(glm::vec3 acceleration, float time);
	
	// folosita atunci cand se ciocnesc mai multe bile simultan
	void addSpeed(glm::vec3 v);
	void calcSpeed();

	float distanceToBall(Ball ball);

	// functia care zice daca este in repaus
	bool isStatic();

	bool inHole();
	void setInHole(bool in);
	bool isOut();

protected:
	glm::vec3 positionCenter;
	float radius;
	glm::vec3 color;
	
	std::vector<glm::vec3> v_aux;

	float limitY;

	//componente vitezei:
	glm::vec3 v_abs;
	glm::vec3 v_direction;

	bool in_hole;
};