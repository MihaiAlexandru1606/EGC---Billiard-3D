#include "BilliardTable.h"
#include <iostream>

BilliardTable::BilliardTable()
{
	float dimX = (width - widthManta + dimensionManta) / 2;
	float compX = (dimX + widthManta) / 2;

	float dimZ = radiusHole + dimensionManta / 2;
	float compZ = radiusHole + lenghtManta + dimZ / 2;


	this->component = {
		// Suprafata mesei
		ComponentTable(glm::vec3(0, height - heightSurface / 2, 0), glm::vec3(width, heightSurface, length), std::string("surface")),
		// corpul mesei:
		// fata
		ComponentTable(glm::vec3(0, positionY, (lengthSurface + dimensionManta + lenghtBody) / 2), glm::vec3(widthManta, heightBody, lenghtBody), std::string("body")),
		// spate
		ComponentTable(glm::vec3(0, positionY, -(lengthSurface + dimensionManta + lenghtBody) / 2), glm::vec3(widthManta, heightBody, lenghtBody), std::string("body")),
		// dreapta fata
		ComponentTable(glm::vec3(positionXBody, positionY, positionZBody), glm::vec3(widthBody, heightBody, lenghtManta), std::string("body")),
		// dreapta spate
		ComponentTable(glm::vec3(positionXBody, positionY, -positionZBody), glm::vec3(widthBody, heightBody, lenghtManta), std::string("body")),
		// stanga fata
		ComponentTable(glm::vec3(-positionXBody, positionY, positionZBody), glm::vec3(widthBody, heightBody, lenghtManta), std::string("body")),
		// stanga spate
		ComponentTable(glm::vec3(-positionXBody, positionY, -positionZBody), glm::vec3(widthBody, heightBody, lenghtManta), std::string("body")),

		// piciorele mesei:
		ComponentTable(glm::vec3(widthSurface / 2, height / 2 - 0.01f, lengthSurface / 2), glm::vec3(0.2f, height, 0.2f), std::string("body")),
		ComponentTable(glm::vec3(-widthSurface / 2, height / 2 - 0.01f, lengthSurface / 2), glm::vec3(0.2f, height, 0.2f), std::string("body")),
		ComponentTable(glm::vec3(-widthSurface / 2, height / 2 - 0.01f, -lengthSurface / 2), glm::vec3(0.2f, height, 0.2f), std::string("body")),
		ComponentTable(glm::vec3(widthSurface / 2, height / 2 - 0.01f, -lengthSurface / 2), glm::vec3(0.2f, height, 0.2f), std::string("body")),

		// 

		ComponentTable(glm::vec3(positionXBody, positionY, 0), glm::vec3(widthBody, heightBody, 2 * radiusHole), std::string("silver")),
		ComponentTable(glm::vec3(-positionXBody, positionY, 0), glm::vec3(widthBody, heightBody, 2 * radiusHole), std::string("silver")),

		ComponentTable(glm::vec3(compX, positionY, (lengthSurface + dimensionManta + lenghtBody) / 2), glm::vec3(dimX, heightBody, lenghtBody), std::string("silver")),
		ComponentTable(glm::vec3(-compX, positionY, (lengthSurface + dimensionManta + lenghtBody) / 2), glm::vec3(dimX, heightBody, lenghtBody), std::string("silver")),
		ComponentTable(glm::vec3(compX, positionY, -(lengthSurface + dimensionManta + lenghtBody) / 2), glm::vec3(dimX, heightBody, lenghtBody), std::string("silver")),
		ComponentTable(glm::vec3(-compX, positionY, -(lengthSurface + dimensionManta + lenghtBody) / 2), glm::vec3(dimX, heightBody, lenghtBody), std::string("silver")),

		ComponentTable(glm::vec3(positionXBody, positionY, compZ), glm::vec3(widthBody, heightBody, dimZ), std::string("silver")),
		ComponentTable(glm::vec3(positionXBody, positionY,-compZ), glm::vec3(widthBody, heightBody, dimZ), std::string("silver")),
		ComponentTable(glm::vec3(-positionXBody, positionY, compZ), glm::vec3(widthBody, heightBody, dimZ), std::string("silver")),
		ComponentTable(glm::vec3(-positionXBody, positionY,-compZ), glm::vec3(widthBody, heightBody, dimZ), std::string("silver")),
	};

	this->holes = {
		// gaura din fata dreapta
		Hole(glm::vec3(positionX, height, positionZ), radiusHole),
		// gaura din fata stanga
		Hole(glm::vec3(-positionX, height, positionZ), radiusHole),
		// gaura din mijloac dreapta
		Hole(glm::vec3(positionX, height, 0), radiusHole),
		// gaura din mijloc stanga
		Hole(glm::vec3(-positionX, height, 0), radiusHole),
		// gaura din spate dreapta
		Hole(glm::vec3(positionX, height, -positionZ), radiusHole),
		// gaura din spate stanga
		Hole(glm::vec3(-positionX, height, -positionZ), radiusHole)
	};

	this->manta = {
		// manta din fata
		ComponentTable(glm::vec3(0, height + heightManta / 2, lengthSurface / 2), glm::vec3(widthManta, heightManta, dimensionManta), std::string("manta")),
		// manta din spate
		ComponentTable(glm::vec3(0, height + heightManta / 2, -lengthSurface / 2), glm::vec3(widthManta, heightManta, dimensionManta), std::string("manta")),
		// manta din dreapta fata
		ComponentTable(glm::vec3(widthSurface / 2, height + heightManta / 2, lengthSurface / 4), glm::vec3(dimensionManta, heightManta, lenghtManta), std::string("manta")),
		// manta din dreapta spate
		ComponentTable(glm::vec3(widthSurface / 2, height + heightManta / 2, -lengthSurface / 4), glm::vec3(dimensionManta, heightManta, lenghtManta), std::string("manta")),
		// manta din stanga fata
		ComponentTable(glm::vec3(-widthSurface / 2, height + heightManta / 2, lengthSurface / 4), glm::vec3(dimensionManta, heightManta, lenghtManta), std::string("manta")),
		// manta din stanga spate
		ComponentTable(glm::vec3(-widthSurface / 2, height + heightManta / 2, -lengthSurface / 4), glm::vec3(dimensionManta, heightManta, lenghtManta), std::string("manta"))
	};

	float radius = this->radius + 0.00f;

	this->initPositionWhiteBall = glm::vec3(initPositionWhiteBallX, height + radius, initPositionWhiteBallZ);

	this->initPositionBlackBall = glm::vec3(0, height + radius, -(lengthSurface - dimensionManta) / 2 + 6 * radius - 0.01f);

	// bilele rosi
	this->initPositionRedBalls = {
		glm::vec3(radius * 2, height + radius,-(lengthSurface - dimensionManta) / 2 + 2 * radius + 0.01f),
		glm::vec3(-radius * 4, height + radius,-(lengthSurface - dimensionManta) / 2 + 2 * radius + 0.01f),

		glm::vec3(-radius , height + radius,-(lengthSurface - dimensionManta) / 2 + 4 * radius),
		glm::vec3(radius * 3, height + radius,-(lengthSurface - dimensionManta) / 2 + 4 * radius),

		glm::vec3(-radius * 2, height + radius,-(lengthSurface - dimensionManta) / 2 + 6 * radius - 0.01f),

		glm::vec3(radius, height + radius,-(lengthSurface - dimensionManta) / 2 + 8 * radius - 0.02f),

		glm::vec3(0, height + radius,-(lengthSurface - dimensionManta) / 2 + 10 * radius - 0.03f)
	};

	// bilele galbene
	this->initPositionYellowBalls = {
		glm::vec3(0, height + radius,-(lengthSurface - dimensionManta) / 2 + 2 * radius + 0.01f),
		glm::vec3(-radius * 2, height + radius,-(lengthSurface - dimensionManta) / 2 + 2 * radius + 0.01f),
		glm::vec3(radius * 4, height + radius,-(lengthSurface - dimensionManta) / 2 + 2 * radius + 0.01f),

		glm::vec3(radius , height + radius,-(lengthSurface - dimensionManta) / 2 + 4 * radius),
		glm::vec3(-radius * 3, height + radius,-(lengthSurface - dimensionManta) / 2 + 4 * radius),

		glm::vec3(radius * 2, height + radius,-(lengthSurface - dimensionManta) / 2 + 6 * radius - 0.01f),

		glm::vec3(-radius, height + radius,-(lengthSurface - dimensionManta) / 2 + 8 * radius - 0.02f)
	};

}

BilliardTable::~BilliardTable()
{
}

std::vector<ComponentTable> BilliardTable::getComponent()
{
	return this->component;
}

std::vector<Hole> BilliardTable::getHoles()
{
	return this->holes;
}

std::vector<ComponentTable> BilliardTable::getManta()
{
	return this->manta;
}

glm::vec3 BilliardTable::getInitPositionWhiteBall()
{
	return this->initPositionWhiteBall;
}

glm::vec3 BilliardTable::getInitPositionBlackBall()
{
	return this->initPositionBlackBall;
}

std::vector<glm::vec3> BilliardTable::getInitPositionRedBalls()
{
	return this->initPositionRedBalls;
}

std::vector<glm::vec3> BilliardTable::getInitPositionYellowBalls()
{
	return this->initPositionYellowBalls;
}

float BilliardTable::getRadius()
{
	return this->radius;
}

bool BilliardTable::canMoveWhileBall(glm::vec3 position)
{
	float x = position.x;
	float z = position.z;

	if (std::fabs(x) + radius > limitX)
		return false;


	if (z + radius > limitZ || z + radius < limitZ  / 3)
		return false;

	float distCmp = (radius + radiusHole) * (radius + radiusHole);

	for (Hole hole : this->holes) {
		float dist = (hole.getPosition().x - x) * (hole.getPosition().x - x) + (hole.getPosition().z - z) * (hole.getPosition().z - z);

		if (dist <= distCmp)
			return false;
	}

	return true;
}

bool BilliardTable::canMoveWhileBall2(glm::vec3 position)
{
	float x = position.x;
	float z = position.z;

	float cmpX = (widthSurface - dimensionManta) / 2 - radius;
	float cmpZ = (lengthSurface - dimensionManta) / 2 - radius;

	if (std::fabs(x) >= cmpX) {
		return false;
	}

	if (std::fabs(z) >= cmpZ) {
		return false;
	}

	float distCmp = (radius + radiusHole) * (radius + radiusHole);

	for (Hole hole : this->holes) {
		float dist = (hole.getPosition().x - x) * (hole.getPosition().x - x) + (hole.getPosition().z - z) * (hole.getPosition().z - z);

		if (dist <= distCmp)
			return false;
	}

	return true;
}

float BilliardTable::getOxLimit()
{
	return limitX;
}

float BilliardTable::getOzLimit()
{
	return limitZ;
}

glm::vec3 BilliardTable::getCenter()
{
	return glm::vec3(0, height, -0.05);
}

