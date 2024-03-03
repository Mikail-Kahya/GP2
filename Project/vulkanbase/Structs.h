#pragma once
#include <optional>

#include "glm/glm.hpp"

struct Vertex
{
	glm::vec2 pos{};
	glm::vec3 color{};
};

struct QueueFamilyIndices {
	std::optional<uint32_t> queueFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete() {
		return queueFamily.has_value() && presentFamily.has_value();
	}
};