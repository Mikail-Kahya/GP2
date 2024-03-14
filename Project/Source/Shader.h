#pragma once
#include <string>
#include <vector>
#include <vulkan/vulkan_core.h>

#include "Structs.h"

class Shader final
{
public:
	Shader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
	~Shader() = default;

	Shader(const Shader& other)					= delete;
	Shader(Shader&& other) noexcept				= delete;
	Shader& operator=(const Shader& other)		= delete;
	Shader& operator=(Shader&& other) noexcept	= delete;

	bool operator==(uint32_t hash) const { return m_Hash == hash; }

	void Initialize(const VkDevice& vkDevice);
	const std::vector<VkPipelineShaderStageCreateInfo>& GetShaderStages() const;
	void DestroyModules(const VkDevice& vkDevice);

	VkPipelineVertexInputStateCreateInfo CreateVertexInputStateInfo() const;
	VkPipelineInputAssemblyStateCreateInfo CreateInputAssemblyStateInfo() const;

	void Start() const;
	void Record(const std::vector<Vertex>& vertices);
	void End() const;
	void Reset() const;

	uint32_t GetHash() const;
	static uint32_t CalcHash(const std::string& vertex, const std::string& fragment);

private:
	VkPipelineShaderStageCreateInfo CreateShaderStageInfo(const VkDevice& device, const std::string& fileName, VkShaderStageFlagBits stage) const;
	VkPipelineShaderStageCreateInfo CreateVertexShaderInfo(const VkDevice& device, const std::string& fileName) const;
	VkPipelineShaderStageCreateInfo CreateFragmentShaderInfo(const VkDevice& device, const std::string& fileName) const;
	VkShaderModule CreateShaderModule(const VkDevice& device, const std::vector<char>& code) const;

	inline static const std::string SHADER_FOLDER{ "shaders/" };
	inline static const std::string EXTENSION{ ".spv" };

	uint32_t m_Hash{};

	const std::string m_VertexShaderFile{};
	const std::string m_FragmentShaderFile{};

	// Every shader holds their command buffer that the renderer will access
	VkCommandBuffer m_CommandBuffer{};
	std::vector<VkPipelineShaderStageCreateInfo> m_ShaderStages{};
};
