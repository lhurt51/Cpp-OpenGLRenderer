#pragma once

#include "Transform.h"
#include "GameObject.h"
#include "Input\Input.h"

class RenderingEngine;
class Shader;

class GameComponent
{

	GameObject* m_parent;

public:

	virtual ~GameComponent() {}

	virtual void ProcessInput(const Input& input, float delta) {}
	virtual void Update(float delta) {}
	virtual void Render(const Shader& shader, const RenderingEngine& renderingEngine) const {}

	virtual void AddToEngine(CoreEngine* engine) const {}

	inline void SetParent(GameObject* parent) { m_parent = parent; }
	inline Transform* GetTransform() { return m_parent->GetTransform(); }
	inline const Transform& GetTransform() const { return *m_parent->GetTransform(); }

};
