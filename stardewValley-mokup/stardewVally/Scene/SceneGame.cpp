#include "stdafx.h"
#include "SceneGame.h"
#include "TileMap.h"
#include "SpriteGo.h"
#include "Player.h"
#include "NpcMgr.h"
#include "Shop.h"
#include "Collider.h"
#include "TimeMoneyUi.h"
#include "Inventory.h"
#include "QuickBar.h"

SceneGame::SceneGame() 
	: Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	texIds.push_back("graphics/testC.png");
	texIds.push_back("graphics/npcTalk.png");
	texIds.push_back("graphics/npcTest.png");
	texIds.push_back("graphics/uitest.png");
	texIds.push_back("graphics/shop_bg.png");
	texIds.push_back(INVEN_IMG_PATH"ItemSlot.png");

	texIds.push_back("graphics/parsnip_seeds.png");
	texIds.push_back("graphics/cauliflower_seeds.png");
	texIds.push_back("graphics/potato_seeds.png");
	texIds.push_back("graphics/garlic_seeds.png");

	texIds.push_back("graphics/portraitsBox.png");
	texIds.push_back("graphics/Pierre.png");
	texIds.push_back("graphics/itemSlot_bg.png");

	texIds.push_back(INVEN_IMG_PATH"CraftImage.bmp");

	texIds.push_back("graphics/clock.png");
	texIds.push_back("graphics/moneyFont.png");
	//texIds.push_back("graphics/³¯¾¾.bmp");

	fontIds.push_back("fonts/DOSGothic.ttf");

	inventory = new Inventory(INVEN_IMG_PATH"CraftImage.bmp");
	quickBar = new QuickBar(INVEN_IMG_PATH"CraftImage.bmp");

	inventory->sortingLayer = SortingLayers::UI;
	quickBar->sortingLayer = SortingLayers::UI;
	
	AddGameObject(inventory);
	AddGameObject(quickBar);
	inventory->SetQuickBar(quickBar);

	timemoney = (TimeMoneyUi*)AddGameObject(new TimeMoneyUi());
	npc = new NpcMgr("Npc");
	player = new Player("Player");

	shop = new Shop("shop");
	shop->SetInventory(inventory);
	shop->SetPlayer(player);
	shop->SetTimeMoeyUi(timemoney);
	AddGameObject(shop);

	player->SetNpcMgr(npc);    
	player->SetInventory(inventory);
	npc->SetPlayer(player);

	AddGameObject(player);
	AddGameObject(npc);

	itemDataMgr::Instance().LoadJson("data/Item.json");

	const auto& items = itemDataMgr::Instance().GetItem("Pierre's General Store");

	for (const auto& item : items)
	{
		TEXTURE_MGR.Load(item.itemTextureId);
	}

	collider = new Collider("Collider");
	AddGameObject(collider);

	/*npc->setTalkCallBack([this]() {
		someUi->ShowHint("something...blabla");
		});*/

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


//>>>>>>>>> Temporary merge branch 2

	Scene::Init();
}

void SceneGame::Enter()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(true);

	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	worldView.setSize(windowSize);
	worldView.setCenter({0.f, 0.f});

	uiView.setSize(windowSize);
	uiView.setCenter({windowSize.x * 0.5f , windowSize.y * 0.5f});
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

