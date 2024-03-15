#include "RendererVulkan.h"

#include "VulkanImpl.h"

RendererVulkan::RendererVulkan()
{
	m_VulkanImp = std::make_unique<VulkanImpl>();
}
