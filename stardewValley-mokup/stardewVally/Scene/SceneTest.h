#pragma once
#include "Scene.h"
#include "TileMap.h"
#include "Shop.h"
#include "SceneHome.h"
#include "TimeMoneyUi.h"

class TimeMoneyUi;
class Player;
class NpcMgr;
class Shop;
class Collider;
class TimeMoneyUi;
class Map;
class Inventory;
class QuickBar;
class DialogueBox;
class Crops;

class SceneTest : public Scene
{
protected:
	Player* player = nullptr;
	NpcMgr* npc = nullptr;
	Shop* shop = nullptr;
	Collider* collider = nullptr;
	TimeMoneyUi* timemoney = nullptr;
	Inventory* inventory = nullptr;
	QuickBar* quickBar = nullptr;
	DialogueBox* dialogueBox = nullptr;

	std::list<Crops*> cropsList;

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

	void CenterView();

	void AddCrops(Crops* crops);
	std::list<Crops*> GetCrops();
};

