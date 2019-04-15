#pragma once

#include "Texture.h"
#include "MappedValues.h"

class Material : public MappedValues
{

public:

	Material() {}

	Material(Texture* diffuse, float specularIntensity, float specularPower, Texture* normalMap = new Texture("default_normal.jpg"), Texture* dispMap = new Texture("default_disp.png"), float dispMapScale = 0.0f, float dispMapOffset = 0.0f)
	{
		SetTexture("diffuse", diffuse);
		SetFloat("specularIntensity", specularIntensity);
		SetFloat("specularPower", specularPower);
		SetTexture("normalMap", normalMap);
		SetTexture("dispMap", dispMap);

		float baseBias = dispMapScale / 2.0f;
		SetFloat("dispMapScale", dispMapScale);
		SetFloat("dispMapBias", -baseBias + baseBias * dispMapOffset);
	}


};