#pragma once

#include <map>

#include "../../../Rendering/Texture/Texture.h"
#include "../Math/MathUtils.h"

class MappedValues
{

	std::map<std::string, Vector3f>	m_vector3fMap;
	std::map<std::string, float>	m_floatMap;
	std::map<std::string, Texture>	m_textureMap;

	Texture							m_defaultTexture;
	Vector3f						m_defaultVector3f;

public:

	MappedValues() : m_defaultTexture(Texture("defaultTexture.png")), m_defaultVector3f(Vector3f(0,0,0))
	{}

	inline void SetVector3f(const std::string& name, const Vector3f& value)	{ m_vector3fMap[name] = value; }
	inline void SetFloat(const std::string& name, float value)				{ m_floatMap[name] = value; }
	inline void SetTexture(const std::string& name, const Texture& value)	{ m_textureMap[name] = value; }

	const Vector3f& GetVector3f(const std::string& name) const;
	float GetFloat(const std::string& name) const;
	const Texture& GetTexture(const std::string& name) const;

};
