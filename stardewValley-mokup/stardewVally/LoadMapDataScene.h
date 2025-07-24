#pragma once
#include "Scene.h"
#include "TileMap.h"
class LoadMapDataScene : public Scene
{
private:
	TileMap* tile;	
	sf::VertexArray va;
public:
	LoadMapDataScene();
	~LoadMapDataScene() override = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	
};

