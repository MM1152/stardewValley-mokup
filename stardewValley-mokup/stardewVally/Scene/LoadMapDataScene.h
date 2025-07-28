#pragma once
#include "Scene.h"
#include "TileMap.h"
class LoadMapDataScene : public Scene
{
private:
	TileMap* tile;	
	TileMap* forGround;

	Map map;

	bool drawCollider;
public:
	LoadMapDataScene();
	~LoadMapDataScene() override = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Draw(sf::RenderWindow& window);
	void Update(float dt) override;
	
};

