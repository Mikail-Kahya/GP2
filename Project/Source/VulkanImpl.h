#pragma once
#include <vector>
#include <vulkan/vulkan_core.h>

#include "GLFW/glfw3.h"

class Shader;

class VulkanImpl final
{
public:
	VulkanImpl();
	~VulkanImpl();

	VulkanImpl(const VulkanImpl& other) = default;
	VulkanImpl(VulkanImpl&& other) noexcept = default;
	VulkanImpl& operator=(const VulkanImpl& other) = default;
	VulkanImpl& operator=(VulkanImpl&& other) noexcept = default;

private:
	void CreateGLFWWindow();
	void CreateInstance();
	void SetupDebugMessenger();
	void CreateSurface();

	void PickPhysicalDevice();
	void CreateLogicalDevice();

	void CreateSwapChain();
	void CreateImageViews();

	void CreateRenderPass();
	void CreateGraphicsPipeline(Shader* shader);
	void CreateFrameBuffers();

	void CreateCommandPool();

	inline static const std::vector<const char*> VALIDATION_LAYERS{ "VK_LAYER_KHRONOS_validation" };

	GLFWwindow* m_WindowPtr{};
	VkInstance m_Instance{};
	VkDebugUtilsMessengerEXT m_DebugMessenger{};

	VkSurfaceKHR m_Surface{};
	VkPhysicalDevice m_PhysicalDevice{};
	VkDevice m_Device{};

	VkQueue m_GraphicsQueue{};
	VkQueue m_PresentQueue{};

	VkSwapchainKHR m_SwapChain{};
	std::vector<VkImageView> m_SwapChainImageViews{};
	std::vector<VkImage> m_SwapChainImages{};
	VkFormat m_SwapChainImageFormat{};
	VkExtent2D m_SwapChainExtent{};

	std::vector<VkFramebuffer> m_SwapChainFramebuffers{};
	VkRenderPass m_RenderPass{};
	VkPipelineLayout m_PipelineLayout{};
	VkPipeline m_GraphicsPipeline{};

	VkCommandPool m_CommandPool{};
};
