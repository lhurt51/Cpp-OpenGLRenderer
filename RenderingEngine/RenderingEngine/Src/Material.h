#pragma once

#include "Texture.h"
#include "MappedValues.h"

class Material : public MappedValues
{

public:

	Material() {}

	Material(const Texture& diffuse, float specularIntensity, float specularPower, const Texture& normalMap = Texture("default_normal.jpg"), const Texture& dispMap = Texture("default_disp.png"), float dispMapScale = 0.0f, float dispMapOffset = 0.0f);

};