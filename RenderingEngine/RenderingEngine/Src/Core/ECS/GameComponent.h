#pragma once

#include "Transform.h"
#include "GameObject.h"
#include "../Input/Input.h"

class RenderingEngine;
class Shader;

class GameComponent
{

	GameObject* m_parent;

public:

	GameComponent() : m_parent(0)
	{}
	virtual ~GameComponent()
	{}

	virtual void ProcessInput(const Input& input, float delta) {}
	virtual void Update(float delta) {}
	virtual void Render(const Shader& shader, const RenderingEngine& renderingEngine, const Camera& camera) const {}

	virtual void AddToEngine(CoreEngine* engine) const {}

	inline Transform* GetTransform() { return m_parent->GetTransform(); }
	inline const Transform& GetTransform() const { return *m_parent->GetTransform(); }

	virtual void SetParent(GameObject* parent) { m_parent = parent; }

};
