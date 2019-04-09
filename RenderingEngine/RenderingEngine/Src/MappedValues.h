#pragma once

#include <map>
#include <string>
#include "Utils\Math\MathUtils.h"

class MappedValues
{

	std::map<std::string, Vector3f> m_vector3fMap;
	std::map<std::string, float> m_floatMap;

public:

	inline void AddVector3f(const std::string& name, Vector3f value) { m_vector3fMap.insert(std::pair<std::string, Vector3f>(name, value)); }
	inline void AddFloat(const std::string& name, float value) { m_floatMap.insert(std::pair<std::string, float>(name, value)); }

	inline Vector3f GetVector3f(const std::string& name) const
	{
		std::map<std::string, float>::const_iterator it = m_floatMap.find(name);
		if (it != m_floatMap.end())
			return it->second;
		return 0;
	}

	inline float GetFloat(const std::string& name) const
	{
		std::map<std::string, float>::const_iterator it = m_floatMap.find(name);
		if (it != m_floatMap.end())
			return it->second;

		return 0;
	}

};