#pragma once
#include "Scene.h"
#include "TileMap.h"
#include "Shop.h"
#include "SceneFarm.h"
#include "TimeMoneyUi.h"

class TimeMoneyUi;
class Player;
class Collider;
class TimeMoneyUi;
class Map;
class Inventory;
class QuickBar;

class SceneHome : public Scene
{
protected:
	TileMap* tile;
	TileMap* forGround;

	Map map;

	bool drawCollider;

public:
	SceneHome();
	~SceneHome() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;


	void Draw(sf::RenderWindow& window) override;
};

