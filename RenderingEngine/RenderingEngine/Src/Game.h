#pragma once

#include "GameObject.h"
#include "CoreEngine.h"

class Game
{

	GameObject m_root;

public:

	Game()
	{}

	virtual ~Game()
	{}

	virtual void Init()
	{}

	void Input(float delta);
	void Update(float delta);
	void Render(RenderingEngine* renderingEngine);

	inline GameObject& GetRoot() { return m_root; }

	inline void SetEngine(CoreEngine* engine) { m_root.SetEngine(engine); }

protected:

	void AddToScene(GameObject* child) { m_root.AddChild(child); }

};

