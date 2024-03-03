#pragma once
#include <vector>

#include "vulkan/vulkan_core.h"
#include "vulkanbase/Structs.h"

class Renderer final
{
public:
	Renderer() = default;
	~Renderer();

	Renderer(const Renderer& other)					= default;
	Renderer(Renderer&& other) noexcept				= default;
	Renderer& operator=(const Renderer& other)		= default;
	Renderer& operator=(Renderer&& other) noexcept	= default;

	void Init(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
	void Init(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, VkDevice device, VkRenderPass renderPass,
		const std::vector<VkFramebuffer>& swapChain,
		VkExtent2D swapChainExtent, VkPipeline graphicsPipeline);

	void RecordCommand(uint32_t imageIdx);
	VkCommandBuffer& GetBuffer();

private:
	void CreateCommandPool(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
	void CreateCommandBuffer(VkCommandBufferLevel bufferType = VK_COMMAND_BUFFER_LEVEL_PRIMARY);

	void RecordDrawFrame(uint32_t imageIdx);

	void DrawFrame(uint32_t imageIdx) const;
	void DrawScene() const;

	VkDevice m_Device{};
	VkCommandPool m_CommandPool{};
	VkCommandBuffer m_CommandBuffer{};

	// Temp
	VkRenderPass m_RenderPass{};
	const std::vector<VkFramebuffer>* m_SwapChainPtr{};
	VkExtent2D m_SwapChainExtent{};
	VkPipeline m_GraphicsPipeline{};
};
