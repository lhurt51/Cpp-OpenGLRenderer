#pragma once

#include "GameObject.h"
#include "CoreEngine.h"
#include "Camera.h"

class Game
{

	ProfileTimer	m_updatetimer;
	ProfileTimer	m_inputTimer;
	GameObject		m_root;

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

	inline double DisplayInputTime(double dividend) { return m_inputTimer.DisplayAndReset("Input Time: ", dividend); }
	inline double DisplayUpdateTime(double dividend) { return m_inputTimer.DisplayAndReset("Update Time: ", dividend); }

	inline void SetEngine(CoreEngine* engine) { m_root.SetEngine(engine); }

protected:

	void AddToScene(GameObject* child) { m_root.AddChild(child); }

};

