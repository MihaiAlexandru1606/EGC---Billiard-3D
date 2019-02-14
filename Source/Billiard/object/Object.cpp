#include "Object.h"

Object::Object()
{
}

Object::~Object()
{
}

std::tuple<std::vector<VertexFormat>, std::vector<unsigned short>, std::string> Object::getInfo()
{
	return std::tuple<std::vector<VertexFormat>, std::vector<unsigned short>, std::string>(vertices, indices, name);
}
