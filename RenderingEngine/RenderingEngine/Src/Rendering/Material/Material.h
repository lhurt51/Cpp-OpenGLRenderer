#pragma once

#include "../Texture/Texture.h"
#include "../../Core/Utils/Math/MathUtils.h"
#include "../../Core/Utils/AssetManager/MappedValues.h"

class MaterialData : public ReferenceCounter, public MappedValues
{
};

class Material
{

	static std::map<std::string, MaterialData*> s_resourceMap;
	MaterialData* m_materialData;
	std::string m_materialName;

public:

	Material(const std::string& materialName = "");
	Material(const std::string& materialName, const Texture& diffuse, float specularIntensity, float specularPower, const Texture& normalMap = Texture("default_normal.jpg"), const Texture& dispMap = Texture("default_disp.png"), float dispMapScale = 0.0f, float dispMapOffset = 0.0f);
	Material(const Material& other);
	virtual ~Material(void);

	inline const Vector3f& GetVector3f(const std::string& name) const { return m_materialData->GetVector3f(name); }
	inline float GetFloat(const std::string& name) const { return m_materialData->GetFloat(name); }
	inline const Texture& GetTexture(const std::string& name) const { return m_materialData->GetTexture(name); }

	inline void SetVector3f(const std::string& name, const Vector3f& value) { m_materialData->SetVector3f(name, value); }
	inline void SetFloat(const std::string& name, float value) { m_materialData->SetFloat(name, value); }
	inline void SetTexture(const std::string& name, const Texture& value) { m_materialData->SetTexture(name, value); }

};