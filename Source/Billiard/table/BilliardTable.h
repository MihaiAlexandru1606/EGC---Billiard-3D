#pragma once

#include <vector>
#include <string>

#include "ComponentTable.h"
#include "Hole.h"
#include <Billiard/ball/Ball.h>
#include <Billiard/ball/WhiteBall.h>

class BilliardTable
{
public:
	BilliardTable();
	~BilliardTable();
	
	std::vector<ComponentTable> getComponent();
	std::vector<Hole> getHoles();
	std::vector<ComponentTable> getManta();
	
	glm::vec3 getInitPositionWhiteBall();
	glm::vec3 getInitPositionBlackBall();
	std::vector<glm::vec3> getInitPositionRedBalls();
	std::vector<glm::vec3> getInitPositionYellowBalls();
	float getRadius();

	bool canMoveWhileBall(glm::vec3 position);
	bool canMoveWhileBall2(glm::vec3 position);
	
	float getOxLimit();
	float getOzLimit();

	const float coef = 0.35f;

	glm::vec3 getCenter();

private:
	std::vector<ComponentTable> component;
	std::vector<Hole> holes;
	std::vector<ComponentTable> manta;

	glm::vec3 initPositionWhiteBall;
	glm::vec3 initPositionBlackBall;
	std::vector<glm::vec3> initPositionRedBalls;
	std::vector<glm::vec3> initPositionYellowBalls;


	// dimensiunile in metri:
	const float height = 0.8f;
	const float length = 2.82f;
	const float width = 1.58f;
	
	const float heightSurface = 0.2f;
	const float lengthSurface = 2.54f;
	const float widthSurface = 1.28f;

	// raza unei gauri
	const float radiusHole = 0.1f;
	const float positionX = widthSurface / 2;
	const float positionZ = lengthSurface / 2;

	const float radius = 0.04f;

	const float dimensionManta = 0.04f;
	const float heightManta = radius * 2 * 0.6f;
	const float widthManta = widthSurface - 2 * radiusHole;
	const float lenghtManta = positionZ - 2 * radiusHole;

	// pentru corpul maesei:
	const float heightBody = height / 2;
	const float lenghtBody = (length - lengthSurface) / 2;
	const float widthBody = (width - widthSurface) / 2;
	const float positionY = height + heightManta - heightBody / 2;
	const float positionXBody = (width + widthSurface) / 4 + dimensionManta / 2;
	const float positionZBody = lengthSurface / 4;

	// dimensiea unui colt 
	const float inHole = radiusHole * 0.4f;
	const float widthCorner = (width - widthSurface) / 2 - (radiusHole - inHole);

	// limitele de deplasare petru masa in sistemul xOz
	const float limitX = (widthSurface - dimensionManta) / 2;
	const float limitZ = (lengthSurface - dimensionManta) / 2;

	const float initPositionWhiteBallX = 0;
	const float initPositionWhiteBallZ = limitZ * 2 / 3;
};