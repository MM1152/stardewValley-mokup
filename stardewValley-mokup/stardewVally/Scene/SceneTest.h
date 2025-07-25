#pragma once
#include "Scene.h"
#include "TileMap.h"

class TimeMoneyUi;
class Player;
class NpcMgr;
class Shop;
class Collider;
class TimeMoneyUi;
class Map;


class SceneTest : public Scene
{
protected:

	Player* player = nullptr;
	NpcMgr* npc = nullptr;
	Shop* shop = nullptr;
	Collider* collider = nullptr;
	TimeMoneyUi* timemoney = nullptr;
	TileMap* tile;
	TileMap* forGround;

	Map map;

	bool drawCollider;
public:
	SceneTest();
	~SceneTest() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;

	void Draw(sf::RenderWindow& window) override;
};

