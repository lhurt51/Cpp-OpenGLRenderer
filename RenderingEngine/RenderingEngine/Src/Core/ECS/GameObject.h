#pragma once

#include <vector>

#include "Transform.h"
#include "../Input\Input.h"

class Camera;
class CoreEngine;
class GameComponent;
class Shader;
class RenderingEngine;

class GameObject
{

	std::vector<GameObject*>	m_children;
	std::vector<GameComponent*> m_components;
	Transform					m_transform;
	CoreEngine*					m_coreEngine;

public:

	GameObject(const Vector3f& pos = Vector3f(0,0,0), const Quaternion& rot = Quaternion(0,0,0,1), float scale = 1.0f) :
		m_transform(pos, rot, scale), m_coreEngine(0)
	{}
	virtual ~GameObject();

	GameObject* AddChild(GameObject* child);
	GameObject* AddComponent(GameComponent* component);

	void ProcessInputAll(const Input& input, float delta);
	void UpdateAll(float delta);
	void RenderAll(const Shader& shader, const RenderingEngine& renderingEngine, const Camera& camera) const;

	std::vector<GameObject*> GetAllAttached();

	inline Transform* GetTransform() { return &m_transform; }
	void SetEngine(CoreEngine* engine);

private:

	void ProcessInput(const Input& input, float delta);
	void Update(float delta);
	void Render(const Shader& shader, const RenderingEngine& renderingEngine, const Camera& camera) const;

};

