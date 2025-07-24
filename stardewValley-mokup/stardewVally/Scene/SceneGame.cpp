#include "stdafx.h"
#include "SceneGame.h"
#include "TileMap.h"
#include "SpriteGo.h"
#include "Player.h"
#include "NpcMgr.h"
#include "Shop.h"
#include "Collider.h"

SceneGame::SceneGame() 
	: Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	texIds.push_back("graphics/testC.png");
	texIds.push_back("graphics/npcTest.png");
	texIds.push_back("graphics/uitest.png");

	shop = new Shop("shop");
	AddGameObject(shop);

	player = new Player("Player");
	AddGameObject(player);
	
	npc = new NpcMgr("Npc");
	npc->SetPlayer(player);
	AddGameObject(npc);

	collider = new Collider("Collider");
	AddGameObject(collider);

	npc->setCallBack([this]() {
		if (!shop->isUiShowing())
			shop->ShowUi();
		else
			shop->CloseUi();
		});

	Scene::Init();
}

void SceneGame::Enter()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(false);

	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	worldView.setSize(windowSize);
	worldView.setCenter({0.f, 0.f});

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);
	Scene::Enter(); //push_back

}

void SceneGame::Exit()
{	
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	window.setView(uiView);
}

