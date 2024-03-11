#pragma once
#include <vector>
#include "Structs.h"

class Mesh 
{
public:
	Mesh(const std::vector<Vertex>& vertices);

private:
	std::vector<Vertex> m_Vertices{};
};