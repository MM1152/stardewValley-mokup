#include "stdafx.h"
#include "SceneGame.h"
#include "TileMap.h"
#include "SpriteGo.h"
#include "Player.h"
#include "NpcMgr.h"
#include "Shop.h"
#include "Collider.h"
#include "TimeMoneyUi.h"

SceneGame::SceneGame() 
	: Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	texIds.push_back("graphics/testC.png");
	texIds.push_back("graphics/npcTest.png");
	texIds.push_back("graphics/uitest.png");
	texIds.push_back("graphics/parsnip_seeds.png");
	texIds.push_back("graphics/cauliflower_seeds.png");
	worldView.setSize(FRAMEWORK.GetWindowSizeF());
	worldView.setCenter({ FRAMEWORK.GetWindowSizeF().x / 2 , FRAMEWORK.GetWindowSizeF().y / 2 });
	uiView.setSize(FRAMEWORK.GetWindowSizeF());
	uiView.setCenter({ FRAMEWORK.GetWindowSizeF().x / 2 , FRAMEWORK.GetWindowSizeF().y / 2 });

	texIds.push_back("graphics/�ð�.png");
	texIds.push_back("graphics/�� ����.png");
	texIds.push_back("graphics/����.bmp");
	texIds.push_back("graphics/����.bmp");

	fontIds.push_back("fonts/SDMisaeng.ttf");
	fontIds.push_back("fonts/DOSGothic.ttf");
	fontIds.push_back("fonts/DungGeunMo.ttf");

	timemoney = (TimeMoneyUi*)AddGameObject(new TimeMoneyUi());
	npc = new NpcMgr("Npc");
	player = new Player("Player");

	shop = new Shop("shop");
	shop->Init();
	AddGameObject(shop);
	

	player->SetNpcMgr(npc);    
	npc->SetPlayer(player);

	AddGameObject(player);
	AddGameObject(npc);

	itemDataMgr::Instance().LoadJson("data/Item.json");

	collider = new Collider("Collider");
	AddGameObject(collider);

	npc->setCallBack([this]() {
		if (!shop->isUiShowing())
			shop->ShowUi();
		else
			shop->CloseUi();
		});
//>>>>>>>>> Temporary merge branch 2

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

	timemoney->SettingMoney(player->GetMoney());
	timemoney->ResetSettingMoney();
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	window.setView(uiView);
}

