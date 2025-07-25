#pragma once
#include "Scene.h"
#include "Shop.h"

class Player;
class NpcMgr;
class Shop;
class Collider;
class TimeMoneyUi;
class Inventory;
class QuickBar;

class SceneGame : public Scene
{
protected:
	Player* player = nullptr;
	NpcMgr* npc = nullptr;
	Shop* shop = nullptr;
	Collider* collider = nullptr;
	TimeMoneyUi* timemoney = nullptr;
	Inventory* inventory = nullptr;
	QuickBar* quickBar = nullptr;

public:
	SceneGame();
	~SceneGame() override = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

