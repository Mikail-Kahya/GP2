#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Singleton.h"

class Shader;

class ResourceManager final : public Singleton<ResourceManager>
{
public:
	ResourceManager() = default;
	~ResourceManager() = default;

	ResourceManager(const ResourceManager& other)					= delete;
	ResourceManager(ResourceManager&& other) noexcept				= delete;
	ResourceManager& operator=(const ResourceManager& other)		= delete;
	ResourceManager& operator=(ResourceManager&& other) noexcept	= delete;

	// Load obj this way
	static void LoadObj(){}

	Shader* GetShader(const std::string& vertex, const std::string& frag);

private:
	std::vector<std::unique_ptr<Shader>> m_Shaders;
};
