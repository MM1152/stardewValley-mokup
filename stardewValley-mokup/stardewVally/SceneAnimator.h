#pragma once
#include "Scene.h"
class SceneAnimator : public Scene
{
protected:
	std::string filePath;

public:
	SceneAnimator();
	~SceneAnimator() override = default;

	void Init() override;
	void Enter() override;
	void Update(float dt) override;
};

