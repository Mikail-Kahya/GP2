#include "Renderer.h"

#include "vulkanbase/VulkanBase.h"
#include "vulkanbase/VulkanUtil.h"

Renderer::~Renderer()
{
	vkDestroyCommandPool(m_Device, m_CommandPool, nullptr);
}

void Renderer::Init(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface)
{
	CreateCommandPool(physicalDevice, surface);
	CreateCommandBuffer();
}

void Renderer::Init(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, VkDevice device, VkRenderPass renderPass,
	const std::vector<VkFramebuffer>& swapChain, VkExtent2D swapChainExtent, VkPipeline graphicsPipeline)
{
	m_Device = device;
	m_RenderPass = renderPass;
	m_SwapChainPtr = &swapChain;
	m_SwapChainExtent = swapChainExtent;
	m_GraphicsPipeline = graphicsPipeline;

	Init(physicalDevice, surface);
}

void Renderer::RecordCommand(uint32_t imageIdx)
{
	vkResetCommandBuffer(m_CommandBuffer, /*VkCommandBufferResetFlagBits*/ 0);
	RecordDrawFrame(imageIdx);
}

VkCommandBuffer& Renderer::GetBuffer()
{
	return m_CommandBuffer;
}

void Renderer::CreateCommandPool(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface)
{
	QueueFamilyIndices queueFamilyIndices = FindQueueFamilies(physicalDevice, surface);

	VkCommandPoolCreateInfo poolInfo{};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	poolInfo.queueFamilyIndex = queueFamilyIndices.queueFamily.value();

	if (vkCreateCommandPool(m_Device, &poolInfo, nullptr, &m_CommandPool) != VK_SUCCESS) {
		throw std::runtime_error("failed to create command pool!");
	}
}

void Renderer::CreateCommandBuffer(VkCommandBufferLevel bufferType)
{
	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = m_CommandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = 1;

	if (vkAllocateCommandBuffers(m_Device, &allocInfo, &m_CommandBuffer) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate command buffers!");
	}
}

void Renderer::RecordDrawFrame(uint32_t imageIdx)
{
	VkCommandBufferBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = 0; // Optional
	beginInfo.pInheritanceInfo = nullptr; // Optional

	if (vkBeginCommandBuffer(m_CommandBuffer, &beginInfo) != VK_SUCCESS) {
		throw std::runtime_error("failed to begin recording command buffer!");
	}
	DrawFrame(imageIdx);


	if (vkEndCommandBuffer(m_CommandBuffer) != VK_SUCCESS) {
		throw std::runtime_error("failed to record command buffer!");
	}
}

void Renderer::DrawFrame(uint32_t imageIdx) const
{
	VkRenderPassBeginInfo renderPassInfo{};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassInfo.renderPass = m_RenderPass;
	renderPassInfo.framebuffer = (*m_SwapChainPtr)[imageIdx];
	renderPassInfo.renderArea.offset = { 0, 0 };
	renderPassInfo.renderArea.extent = m_SwapChainExtent;
	
	VkClearValue clearColor = { {{0.0f, 0.0f, 0.0f, 1.0f}} };
	renderPassInfo.clearValueCount = 1;
	renderPassInfo.pClearValues = &clearColor;
	
	vkCmdBeginRenderPass(m_CommandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
	
	vkCmdBindPipeline(m_CommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_GraphicsPipeline);
	
	VkViewport viewport{};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = (float)m_SwapChainExtent.width;
	viewport.height = (float)m_SwapChainExtent.height;
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;
	vkCmdSetViewport(m_CommandBuffer, 0, 1, &viewport);
	
	VkRect2D scissor{};
	scissor.offset = { 0, 0 };
	scissor.extent = m_SwapChainExtent;
	vkCmdSetScissor(m_CommandBuffer, 0, 1, &scissor);
	
	DrawScene();
	vkCmdEndRenderPass(m_CommandBuffer);
}

void Renderer::DrawScene() const
{
	vkCmdDraw(m_CommandBuffer, 6, 1, 0, 0);
}
