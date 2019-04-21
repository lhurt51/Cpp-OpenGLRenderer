#include "RenderingEngine.h"
#include "Window.h"
#include "GameObject.h"
#include "Shader.h"
#include <GL/glew.h>
#include "Mesh.h"
#include <cstring>
#include <cassert>

const Matrix4f RenderingEngine::s_biasMatrix = Matrix4f().InitScale(Vector3f(0.5, 0.5, 0.5)) * Matrix4f().InitTranslation(Vector3f(1.0, 1.0, 1.0));

RenderingEngine::RenderingEngine()
{
	// Shader initialization
	m_samplerMap.insert(std::pair<std::string, unsigned int>("diffuse", 0));
	m_samplerMap.insert(std::pair<std::string, unsigned int>("normalMap", 1));
	m_samplerMap.insert(std::pair<std::string, unsigned int>("dispMap", 2));
	m_samplerMap.insert(std::pair<std::string, unsigned int>("shadowMap", 3));

	SetVector3f("ambient", Vector3f(0.2f, 0.2f, 0.2f));
	//SetTexture("shadowMap", new Texture(1024, 1024, 0, GL_TEXTURE_2D, GL_LINEAR, GL_RG32F, GL_RGBA, true, GL_COLOR_ATTACHMENT0));
	//SetTexture("shadowMapTempTarget", new Texture(1024, 1024, 0, GL_TEXTURE_2D, GL_LINEAR, GL_RG32F, GL_RGBA, true, GL_COLOR_ATTACHMENT0));
	m_defaultShader = new Shader("forward-ambient");
	m_shadowMapShader = new Shader("shadowMapGenerator");
	m_nullFilter = new Shader("filter-null");
	m_gausBlurFilter = new Shader("filter-gausBlur7x1");

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP);

	// Render To Texture Init
	m_altCamera = new Camera(Matrix4f().InitIdentity());
	m_altCameraObject = (new GameObject())->AddComponent(m_altCamera);
	m_altCamera->GetTransform().Rotate(Vector3f(0, 1, 0), ToRadians(180.0f));

	int width = Window::GetWidth();
	int height = Window::GetHeight();

	m_tempTarget = new Texture(width, height, 0, GL_TEXTURE_2D, GL_NEAREST, GL_RGBA, GL_RGBA, false, GL_COLOR_ATTACHMENT0);

	m_planeMaterial = new Material(m_tempTarget, 1, 8);
	m_planeTransform.SetScale(1.0f);
	m_planeTransform.Rotate(Quaternion(Vector3f(1, 0, 0), ToRadians(90.0f)));
	m_planeTransform.Rotate(Quaternion(Vector3f(0, 0, 1), ToRadians(180.0f)));
	m_plane = new Mesh("./Res/models/plane.obj");

	for (int i = 0; i < s_numShadowMaps; i++)
	{
		int shadowMapSize = 1 << (i + 1);
		m_shadowMaps[i] = new Texture(shadowMapSize, shadowMapSize, 0, GL_TEXTURE_2D, GL_LINEAR, GL_RG32F, GL_RGBA, true, GL_COLOR_ATTACHMENT0);
		m_shadowTempTargets[i] = new Texture(shadowMapSize, shadowMapSize, 0, GL_TEXTURE_2D, GL_LINEAR, GL_RG32F, GL_RGBA, true, GL_COLOR_ATTACHMENT0);
	}
}

RenderingEngine::~RenderingEngine()
{
	SetTexture("shadowMap", 0);

	if (m_defaultShader) delete m_defaultShader;
	if (m_shadowMapShader) delete m_shadowMapShader;
	if (m_nullFilter) delete m_nullFilter;
	if (m_gausBlurFilter) delete m_gausBlurFilter;
	if (m_altCameraObject) delete m_altCameraObject;
	if (m_planeMaterial) delete m_planeMaterial;
	if (m_plane) delete m_plane;

	for (int i = 0; i < s_numShadowMaps; i++)
	{
		if (m_shadowMaps[i]) delete m_shadowMaps[i];
		if (m_shadowTempTargets[i]) delete m_shadowTempTargets[i];
	}
}

void	RenderingEngine::Render(GameObject* object)
{
	Window::BindAsRenderTarget();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	object->RenderAll(m_defaultShader, this);

	for (unsigned int i = 0; i < m_lights.size(); i++)
	{
		m_activeLight = m_lights[i];
		ShadowInfo* shadowInfo = m_activeLight->GetShadowInfo();

		/*
		GetTexture("shadowMap")->BindAsRenderTarget();
		glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		*/

		if (shadowInfo)
		{
			int shadowMapIndex = shadowInfo->GetShadowMapSizeAsPowerOf2() - 1;

			SetTexture("shadowMap", m_shadowMaps[shadowMapIndex]);
			m_shadowMaps[shadowMapIndex]->BindAsRenderTarget();
			glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

			m_altCamera->SetProjection(shadowInfo->GetProjection());
			m_altCamera->GetTransform().SetPos(m_activeLight->GetTransform().GetTransformedPos());
			m_altCamera->GetTransform().SetRot(m_activeLight->GetTransform().GetTransformedRot());

			m_lightMatrix = s_biasMatrix * m_altCamera->GetViewProjection();

			SetFloat("shadowVarianceMin", shadowInfo->GetMinVariance());
			SetFloat("shadowLightBleedReduction", shadowInfo->GetLightBleedReduction());
			bool flipFaces = shadowInfo->GetFlipFaces();

			Camera* temp = m_mainCamera;
			m_mainCamera = m_altCamera;

			if (flipFaces) glCullFace(GL_FRONT);
			object->RenderAll(m_shadowMapShader, this);
			if (flipFaces) glCullFace(GL_BACK);

			m_mainCamera = temp;

			float shadowSoftness = shadowInfo->GetShadowSoftness();
			if (shadowSoftness != 0)
				BlurShadowMap(shadowMapIndex, shadowSoftness);
		}
		else
		{
			SetTexture("shadowMap", m_shadowMaps[0]);
			m_shadowMaps[0]->BindAsRenderTarget();
			glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
			m_lightMatrix = Matrix4f().InitScale(Vector3f(Vector3f(0, 0, 0)));
			SetFloat("shadowVarianceMin", 0.00002f);
			SetFloat("shadowLightBleedReduction", 0.0f);
		}

		Window::BindAsRenderTarget();

		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		glDepthMask(GL_FALSE);
		glDepthFunc(GL_EQUAL);

		object->RenderAll(m_activeLight->GetShader(), this);

		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LESS);
		glDisable(GL_BLEND);
	}
}

void RenderingEngine::BlurShadowMap(int shadowMapIndex, float blurAmount)
{
	Texture* shadowMap = m_shadowMaps[shadowMapIndex];
	Texture* tempTarget = m_shadowTempTargets[shadowMapIndex];

	SetVector3f("blurScale", Vector3f(blurAmount / shadowMap->GetWidth(), 0.0f, 0.0f));
	ApplyFilter(m_gausBlurFilter, shadowMap, tempTarget);

	SetVector3f("blurScale", Vector3f(0.0f, blurAmount / shadowMap->GetHeight(), 0.0f));
	ApplyFilter(m_gausBlurFilter, tempTarget, shadowMap);
}

void RenderingEngine::ApplyFilter(Shader * filter, Texture * source, Texture * dest)
{
	assert(source != dest);
	if (dest == 0)
		Window::BindAsRenderTarget();
	else
		dest->BindAsRenderTarget();

	SetTexture("filterTexture", source);

	m_altCamera->SetProjection(Matrix4f().InitIdentity());
	m_altCamera->GetTransform().SetPos(Vector3f(0, 0, 0));
	m_altCamera->GetTransform().SetRot(Quaternion(Vector3f(0, 1, 0), ToRadians(180.0f)));

	Camera* temp = m_mainCamera;
	m_mainCamera = m_altCamera;

	glClear(GL_DEPTH_BUFFER_BIT);
	filter->Bind();
	filter->UpdateUniforms(m_planeTransform, *m_planeMaterial, this);
	m_plane->Draw();

	m_mainCamera = temp;
	SetTexture("filterTexture", 0);
}
