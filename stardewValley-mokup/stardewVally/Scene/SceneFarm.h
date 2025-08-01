#pragma once
#include "Scene.h"
#include "TileMap.h"
#include "Shop.h"
#include "SceneHome.h"
#include "TimeMoneyUi.h"
#include "SoundPlayer.h"

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
class DropItem;
class SellBox;
class SoundPlayer;

class SceneFarm : public Scene
{
protected:
	NpcMgr* npc = nullptr;
	Shop* shop = nullptr;
	Collider* collider = nullptr;
	DialogueBox* dialogueBox = nullptr;
	SellBox* sellBox = nullptr;

	std::list<Crops*> cropsList;
	std::vector<InteractionObject*> objects;
	std::list<DropItem*> dropitemList;

	TileMap* tile;
	TileMap* forGround;
	SoundPlayer soundPlayer;

	Map map;

	bool drawCollider;
public:
	SceneFarm();
	~SceneFarm() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;

	void Draw(sf::RenderWindow& window) override;

	void CenterView();

	void AddCrops(Crops* crops);
	void RemoveCrops(Crops* crops);

	void RemoveDropItem(DropItem* dropitem);
	void AddDropItem(DropItem* dropitem);
};

