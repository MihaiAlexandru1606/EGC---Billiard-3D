#pragma once

#include <string>
#include <Core/Engine.h>

class ComponentTable
{
public:

	ComponentTable(glm::vec3 position, glm::vec3 dimension, std::string textureName);
	~ComponentTable();

	glm::vec3 getPosition();
	glm::vec3 getDimension();
	std::string getTextureName();

private:

	glm::vec3 position;
	glm::vec3 dimension;
	std::string textureName;
};