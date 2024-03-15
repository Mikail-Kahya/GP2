#include <algorithm>

#include "ResourceManager.h"
#include "Shader.h"

Shader* ResourceManager::GetShader(const std::string& vertex, const std::string& frag)
{
	const uint32_t hash{ Shader::CalcHash(vertex, frag) };

	const auto foundIt = std::find(m_Shaders.begin(), m_Shaders.end(), hash);
	if (m_Shaders.empty() || foundIt != m_Shaders.end())
	{
		m_Shaders.emplace_back(std::make_unique<Shader>(vertex, frag));
		return m_Shaders.back().get();
	}

	return foundIt->get();
}
