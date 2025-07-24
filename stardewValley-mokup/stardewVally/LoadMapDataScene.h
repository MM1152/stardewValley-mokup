#pragma once
#include "Scene.h"
class LoadMapDataScene : public Scene
{
private:
	
public:
	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	
};

