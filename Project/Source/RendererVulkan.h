#pragma once
#include <memory>

class VulkanImpl;

class RendererVulkan
{
public:
	RendererVulkan();
	~RendererVulkan() = default;

	RendererVulkan(const RendererVulkan& other)					= delete;
	RendererVulkan(RendererVulkan&& other) noexcept				= delete;
	RendererVulkan& operator=(const RendererVulkan& other)		= delete;
	RendererVulkan& operator=(RendererVulkan&& other) noexcept	= delete;

	static int GetWindowWidth() { return WIDTH; }
	static int GetWindowHeight() { return HEIGHT; }

private:
	// Window
	static constexpr int WIDTH{ 800 }, HEIGHT{ 600 };
	std::unique_ptr<VulkanImpl> m_VulkanImp;

};
