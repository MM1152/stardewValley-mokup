#pragma once
#include "Scene.h"
#include "TitleUi.h"

class TitleUi;

class SceneTitle : public Scene
{
protected:

	TitleUi* titleui;

public:
	SceneTitle();
	~SceneTitle() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
};

