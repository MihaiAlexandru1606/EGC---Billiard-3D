#include "ComponentTable.h"

ComponentTable::ComponentTable(glm::vec3 position, glm::vec3 dimension, std::string textureName):
	position(position),
	dimension(dimension),
	textureName(textureName)
{
}

ComponentTable::~ComponentTable()
{
}

glm::vec3 ComponentTable::getPosition()
{
	return this->position;
}

glm::vec3 ComponentTable::getDimension()
{
	return this->dimension;
}

std::string ComponentTable::getTextureName()
{
	return this->textureName;
}
