#pragma once
#include "Scene.h"
#include "TileMap.h"
#include "Shop.h"
#include "SceneHome.h"
#include "TimeMoneyUi.h"
#include "SceneFarm.h"
#include "SceneVillige.h"

class Player;
class Collider;
class TimeMoneyUi;
class Map;
class Inventory;
class QuickBar;

class SceneStore : public Scene
{
protected:
	TileMap* tile;
	TileMap* forGround;

	Map map;

	bool drawCollider;

public:
	SceneStore();
	~SceneStore() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;


	void Draw(sf::RenderWindow& window) override;
};


