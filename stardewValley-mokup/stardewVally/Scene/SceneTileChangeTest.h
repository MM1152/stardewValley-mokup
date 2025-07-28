#pragma once
#include "Scene.h"
#include "Map.h"
#include "TileMap.h"
class SceneTileChangeTest : public Scene
{
private:
	Map map;

	TileMap* tile;
	TileMap* buildTile;

	Player* player;
public:
	SceneTileChangeTest();
	~SceneTileChangeTest() override = default;

	virtual void Init();
	virtual void Release();

	virtual void Enter();
	virtual void Exit();

	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow& window);

};

