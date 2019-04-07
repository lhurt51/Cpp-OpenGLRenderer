#pragma once

#include "Texture.h"
#include "MappedValues.h"

class Material : public MappedValues
{

	std::map<std::string, Texture*> m_textureMap;

public:

	Material() {}

	Material(Texture* diffuse, float specularIntensity, float specularPower)
	{
		AddTexture("diffuse", diffuse);
		AddFloat("specularIntensity", specularIntensity);
		AddFloat("specularPower", specularPower);
	}

	virtual ~Material()
	{
		// Delete all textures
		std::map<std::string, Texture*>::iterator it;
		for (it = m_textureMap.begin(); it != m_textureMap.end(); it++)
			if (it->second) delete it->second;
	}

	inline void AddTexture(const std::string& name, Texture* value) { m_textureMap.insert(std::pair<std::string, Texture*>(name, value)); }

	inline Texture* GetTexture(const std::string& name) const
	{
		std::map<std::string, Texture*>::const_iterator it = m_textureMap.find(name);
		if (it != m_textureMap.end())
			return it->second;
		return 0;
	}


};