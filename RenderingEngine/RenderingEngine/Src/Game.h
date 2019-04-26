#pragma once

#include "GameObject.h"
#include "CoreEngine.h"
#include "Camera.h"

class Game
{

	GameObject m_root;

public:

	Game()
	{}

	virtual ~Game()
	{}

	virtual void Init(const Window& window)
	{}

	void ProcessInput(const Input& input, float delta);
	void Update(float delta);
	void Render(RenderingEngine* renderingEngine, const Camera& camera);

	inline GameObject& GetRoot() { return m_root; }

	inline void SetEngine(CoreEngine* engine) { m_root.SetEngine(engine); }

protected:

	void AddToScene(GameObject* child) { m_root.AddChild(child); }

};

