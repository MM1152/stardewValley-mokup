#pragma once
#include "Scene.h"
#include "TitleUi.h"
#include "SoundPlayer.h"

class TitleUi;

class SceneTitle : public Scene
{
protected:

	TitleUi* titleui;
	SoundPlayer soundPlayer;

public:
	SceneTitle();
	~SceneTitle() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
};

