#include "stdafx.h"
#include "SceneTest.h"
#include "TileMap.h"
#include "SpriteGo.h"
#include "Player.h"
#include "NpcMgr.h"
#include "Shop.h"
#include "Collider.h"
#include "TimeMoneyUi.h"

SceneTest::SceneTest()
	: Scene(SceneIds::Test)
{
}

void SceneTest::Init()
{
	texIds.push_back("graphics/testC.png");
	texIds.push_back("graphics/npcTest.png");
	texIds.push_back("graphics/uitest.png");
	texIds.push_back("graphics/shopSlot_bg.png");

	texIds.push_back("graphics/parsnip_seeds.png");
	texIds.push_back("graphics/cauliflower_seeds.png");

	//Map Load
	texIds.push_back(GRAPHICS_PATH"³óÀå(º½).bmp");
	texIds.push_back(GRAPHICS_PATH"building.png");

	//TimeUi
	texIds.push_back("graphics/½Ã°è.png");
	texIds.push_back("graphics/µ· ¼ýÀÚ.png");
	texIds.push_back("graphics/³¯¾¾.bmp");
	texIds.push_back("graphics/°èÀý.bmp");

	//font
	fontIds.push_back("fonts/SDMisaeng.ttf");
	fontIds.push_back("fonts/DOSGothic.ttf");
	fontIds.push_back("fonts/DungGeunMo.ttf");
	//TimeMoney
	timemoney = (TimeMoneyUi*)AddGameObject(new TimeMoneyUi());
	npc = new NpcMgr("Npc");
	player = new Player("Player");
	//shop
	shop = new Shop("shop");
	shop->Init();
	shop->Reset();
	AddGameObject(shop);
	//player & npc
	player->SetNpcMgr(npc);

	npc->SetPlayer(player);
	AddGameObject(player);
	AddGameObject(npc);


	itemDataMgr::Instance().LoadJson("data/Item.json");
	drawCollider = true;

	npc->setCallBack([this]() {
		if (!shop->isUiShowing())
		{
			shop->ShowUi();
		}
		else
		{
			shop->CloseUi();
		}
		});
	

	tile = new TileMap(VertexType::Game);
	forGround = new TileMap(VertexType::Game);
	AddGameObject(tile);
	AddGameObject(forGround);

	

	Scene::Init();
}

void SceneTest::Enter()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(true);
	worldView.setSize({ FRAMEWORK.GetWindowSizeF().x / 7, FRAMEWORK.GetWindowSizeF().y / 6});
	
	uiView.setSize(FRAMEWORK.GetWindowSizeF());
	uiView.setCenter({ FRAMEWORK.GetWindowSizeF().x / 2 , FRAMEWORK.GetWindowSizeF().y / 2 });

	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	Scene::Enter(); //push_back
	map.Load(MAP_PATH"tes");


	for (auto tri : map.GetTriggers()) {
		tri->Init();
		tri->SetPlayer(player);
		if (tri->GetType() == TriggerType::Door) {
			tri->callback = [this]() {
				SCENE_MGR.ChangeScene(SceneIds::Maptool);
			};
		}
	}


	tile->Set(map.GetTextId(0), map.GetCellDatas(0));
	forGround->Set(map.GetTextId(1), map.GetCellDatas(1));

	player->SetMap(&map);
}

void SceneTest::Exit()
{
	Scene::Exit();
	map.Release();
}

void SceneTest::Update(float dt)
{
	Scene::Update(dt);
	worldView.setCenter(player->GetPosition().x, player->GetPosition().y + 15);
	timemoney->SettingMoney(player->GetMoney());
	timemoney->ResetSettingMoney();

	if (InputMgr::GetKeyDown(sf::Keyboard::F9)) {
		drawCollider = !drawCollider;
	}

	for (auto tri : map.GetTriggers()) {
		tri->Update(dt);
	}
}

void SceneTest::Draw(sf::RenderWindow& window)
{
	
	Scene::Draw(window);
	window.setView(worldView);
	if (drawCollider)
	{
		for (auto col : map.GetColliders())
		{
			window.draw(*col);
		}

		for (auto tri : map.GetTriggers()) {
			tri->Draw(window);
		}
	}

}
