#include "sampling.glh"

bool InRange(float val)
{
	return val >= 0.0 && val <= 1.0;
}

float CalcShadowAmount(sampler2D shadowMap, vec4 initShadowMapCoords)
{
	// Perspective divide same as gl_position but needs to be in a range
	vec3 shadowMapCoords = (initShadowMapCoords.xyz / initShadowMapCoords.w);

	if (InRange(shadowMapCoords.z) && InRange(shadowMapCoords.y) && InRange(shadowMapCoords.x))
	{
		// How far nearest object is from the light
		return SampleVarianceShadowMap(shadowMap, shadowMapCoords.xy, shadowMapCoords.z, R_shadowVarianceMin, R_shadowLightBleedReduction);
	}
	else
	{
		return 1.0;
	}
}

void main ()
{
	vec3 directionToEye = normalize(C_eyePos - worldPos0);
	vec2 texCoords = CalcParallaxTexCoords(dispMap, tbnMatrix, directionToEye, texCoord0, dispMapScale, dispMapBias);
	vec3 normal = normalize(tbnMatrix * (255.0/128.0 * texture2D(normalMap, texCoords).xyz - 1));
	vec4 lightingAmt = CalcLightingEffect(normal, worldPos0) * CalcShadowAmount(R_shadowMap, shadowMapCoords0);

	gl_FragColor = texture2D(diffuse, texCoords) * lightingAmt;
}