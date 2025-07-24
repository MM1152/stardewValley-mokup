#pragma once
#include "Scene.h"

class TimeMoneyUi;

class SceneTest : public Scene
{
protected:

	TimeMoneyUi* timemoney;

public:
	SceneTest();
	~SceneTest() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
};

