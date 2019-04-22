#include "Lighting.h"
#include "../RenderingEngine.h"
#include "../Shader.h"
#include "../CoreEngine.h"
#include <iostream>

#define COLOR_DEPTH 256

ShadowCameraTransform BaseLight::CalcShadowCameraTransform(const Vector3f& mainCameraPos, const Quaternion& mainCameraRot) const
{
	return ShadowCameraTransform(GetTransform().GetTransformedPos(), GetTransform().GetTransformedRot());
}

void BaseLight::AddToEngine(CoreEngine* engine) const
{
	engine->GetRenderingEngine()->AddLight(*this);
}

DirectionalLight::DirectionalLight(const Vector3f& color, float intensity, int shadowMapSizeAsPowerOf2, float shadowArea, float shadowSoftness, float lightBleedReduction, float minVariance) : BaseLight(color, intensity, Shader("forward-directional")), m_halfShadowArea(shadowArea / 2.0f)
{
	if (shadowMapSizeAsPowerOf2 != 0)
	{
		SetShadowInfo(ShadowInfo(Matrix4f().InitOrthographic(-m_halfShadowArea, m_halfShadowArea, -m_halfShadowArea, m_halfShadowArea, -m_halfShadowArea, m_halfShadowArea), true, shadowMapSizeAsPowerOf2, shadowSoftness, lightBleedReduction, minVariance));
	}
}

ShadowCameraTransform DirectionalLight::CalcShadowCameraTransform(const Vector3f & mainCameraPos, const Quaternion & mainCameraRot) const
{
	Vector3f resultPos = mainCameraPos + mainCameraRot.GetForward() * GetHalfShadowArea();
	Quaternion resultRot = GetTransform().GetTransformedRot();

	float worldTexelSize = (GetHalfShadowArea() * 2) / ((float)(1 << GetShadowInfo().GetShadowMapSizeAsPowerOf2()));

	Vector3f lightSpaceCameraPos = resultPos.Rotate(resultRot.Conjugate());

	lightSpaceCameraPos.SetX(worldTexelSize * floor(lightSpaceCameraPos.GetX() / worldTexelSize));
	lightSpaceCameraPos.SetY(worldTexelSize * floor(lightSpaceCameraPos.GetY() / worldTexelSize));

	resultPos = lightSpaceCameraPos.Rotate(resultRot);

	return ShadowCameraTransform(resultPos, resultRot);
}


PointLight::PointLight(const Vector3f& color, float intensity, const Attenuation& atten, const Shader& shader) : BaseLight(color, intensity, shader), m_atten(atten)
{
	float a = m_atten.GetExponent();
	float b = m_atten.GetLinear();
	float c = m_atten.GetConstant() - COLOR_DEPTH * intensity * color.Max();

	m_range = (-b + sqrtf(b * b - 4 * a * c)) / (2 * a);
}

SpotLight::SpotLight(const Vector3f& color, float intensity, const Attenuation& atten, float viewAngle, int shadowMapSizeAsPowerOf2, float shadowSoftness, float lightBleedReduction, float minVariance) : PointLight(color, intensity, atten, Shader("forward-spot")), m_cutoff(cos(viewAngle/2))
{
	if (shadowMapSizeAsPowerOf2 != 0)
	{
		SetShadowInfo(ShadowInfo(Matrix4f().InitPerspective(viewAngle, 1.0, 0.1, GetRange()), false, shadowMapSizeAsPowerOf2, shadowSoftness, lightBleedReduction, minVariance));
	}
}
