#pragma once

#include <vector>
#include <string>
#include <tuple>

#include <Core/Engine.h>

class Object
{
public:
	Object();
	~Object();
	
	std::tuple<std::vector<VertexFormat>, std::vector<unsigned short>, std::string> getInfo();

protected:

	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;
	std::string name;
};
