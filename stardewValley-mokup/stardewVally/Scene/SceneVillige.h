#pragma once
#include "Scene.h"
#include "TileMap.h"
#include "Shop.h"
#include "SceneHome.h"
#include "TimeMoneyUi.h"
#include "SceneFarm.h"
#include "SceneStore.h"

class Player;
class Collider;
class TimeMoneyUi;
class Map;
class Inventory;
class QuickBar;
class DialogueBox;
class NpcMgr;

class SceneVillige : public Scene
{
protected:
	TileMap* tile;
	TileMap* forGround;
	DialogueBox* dialogueBox;
	NpcMgr* npc;
	Map map;

	bool drawCollider;

public:
	SceneVillige();
	~SceneVillige() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;


	void Draw(sf::RenderWindow& window) override;

	void CenterView();
};

