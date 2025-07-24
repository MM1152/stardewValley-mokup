#pragma once
#include "Scene.h"
#include "TileMap.h"
class LoadMapDataScene : public Scene
{
private:
	TileMap* tile;	
	Map map;
public:
	LoadMapDataScene();
	~LoadMapDataScene() override = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	
};

