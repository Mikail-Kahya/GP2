#pragma once
#include <optional>
#include <array>

#include "vulkan/vulkan_core.h"
#include "glm/glm.hpp"

struct Vertex
{
private:
	static constexpr int NR_ATTRIBUTES{ 2 };

public:
	using Attributes = std::array<VkVertexInputAttributeDescription, NR_ATTRIBUTES>;

	glm::vec2 pos{};
	glm::vec3 color{};

	static VkVertexInputBindingDescription GetBindingDescription()
	{
		VkVertexInputBindingDescription bindingDescription{};
		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(Vertex);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		return bindingDescription;
	}

	static Attributes GetAttributeDescriptions()
	{
		Attributes attributeDescriptions{};
		// Pos
		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, pos);

		// Color
		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, color);

		return attributeDescriptions;
	}
};

struct QueueFamilyIndices {
	std::optional<uint32_t> queueFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete() {
		return queueFamily.has_value() && presentFamily.has_value();
	}
};

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};