#pragma once

#include <vulkan/vulkan_core.h>

class VulkanObserver final 
{
public:
	
	~VulkanObserver() = default;

	VulkanObserver(const VulkanObserver& other) = default;
	VulkanObserver(VulkanObserver&& other) noexcept = default;
	VulkanObserver& operator=(const VulkanObserver& other) = default;
	VulkanObserver& operator=(VulkanObserver&& other) noexcept = default;

	static VkDevice GetDevice() { return device; }
	static VkPhysicalDevice GetPhysicalDevice() { return m_PhysicalDevice; }

private:
	VulkanObserver() = default;
	friend class VulkanImpl;

	inline static VkDevice m_Device{};
	inline static VkPhysicalDevice m_PhysicalDevice{};
};