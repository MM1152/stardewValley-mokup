#include "stdafx.h"
#include "SceneTest.h"
#include "TileMap.h"
#include "SpriteGo.h"
#include "Player.h"
#include "NpcMgr.h"
#include "Shop.h"
#include "Collider.h"
#include "TimeMoneyUi.h"
#include "Inventory.h"
#include "QuickBar.h"

SceneTest::SceneTest()
	: Scene(SceneIds::Test)
{
}

void SceneTest::Init()
{
	texIds.push_back(GRAPHICS_PATH"tools.png");
	texIds.push_back(GRAPHICS_PATH"farmer_base.png");
	texIds.push_back(GRAPHICS_PATH"hats.png");
	texIds.push_back("graphics/testC.png");
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

	//Map Load
	texIds.push_back(GRAPHICS_PATH"spring.bmp");
	texIds.push_back(GRAPHICS_PATH"building.png");

	//TimeUi
	texIds.push_back("graphics/clock.png");
	texIds.push_back("graphics/moneyFont.png");
	//texIds.push_back("graphics/날씨.bmp");
	//texIds.push_back("graphics/계절.bmp");

	//font
	fontIds.push_back("fonts/DOSGothic.ttf");

	//crops
	texIds.push_back("graphics/parsnisip.png");


	inventory = new Inventory(INVEN_IMG_PATH"CraftImage.bmp");
	quickBar = new QuickBar(INVEN_IMG_PATH"CraftImage.bmp");
	npc = new NpcMgr("Npc");
	player = new Player("Player");
	timemoney = new TimeMoneyUi("TimeMoney");
	shop = new Shop("shop");
	
	AddGameObject(inventory);
	AddGameObject(quickBar);
	inventory->SetQuickBar(quickBar);

	//TimeMoney

	timemoney->Setplayer(player);
	AddGameObject(timemoney);
	
	//shop
	shop->SetInventory(inventory);
	shop->SetPlayer(player);
	shop->SetTimeMoeyUi(timemoney);
	AddGameObject(shop);
	//player & npc

	player->SetNpcMgr(npc);
	player->SetInventory(inventory);
	player->SetTimer(timemoney);
	npc->SetPlayer(player);
	npc->SetTimer(timemoney);
	npc->SetInventory(inventory);
	AddGameObject(player);
	AddGameObject(npc);

	const auto& items = itemDataMgr::Instance().GetShopItemList("Pierre's General Store");

	for (const auto& item : items)
	{
		texIds.push_back(item.itemTextureId);
	}

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

	map.Init(tile, forGround);
	// F9 Draw Collider
	drawCollider = true;


	Scene::Init();
}

void SceneTest::Enter()
{
	//player->SetPosition({ 208.f, 190.f });

	FRAMEWORK.GetWindow().setMouseCursorVisible(true);
	worldView.setSize({ FRAMEWORK.GetWindowSizeF().x / 6, FRAMEWORK.GetWindowSizeF().y / 6 });

	uiView.setSize(FRAMEWORK.GetWindowSizeF());
	uiView.setCenter({ FRAMEWORK.GetWindowSizeF().x / 2 , FRAMEWORK.GetWindowSizeF().y / 2 });

	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	Scene::Enter(); //push_back
	player->SetPosition({ 208.f, 250.f });

	map.Load(MAP_PATH"demomap");

	for (auto tri : map.GetTriggers()) {
		tri->Init();
		tri->SetPlayer(player);
		if (tri->GetType() == TriggerType::Door) {
			tri->callback = [this]() {
				SCENE_MGR.ChangeScene(SceneIds::Home);
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
	CenterView();

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

void SceneTest::CenterView()
{
	// left view
	if (player->GetPosition().x <= tile->GetLocalBounds().left + worldView.getSize().x / 2 &&
		player->GetPosition().y <= tile->GetLocalBounds().top + worldView.getSize().y / 2)
	{
		worldView.setCenter(tile->GetLocalBounds().left + worldView.getSize().x / 2,
			tile->GetLocalBounds().top + worldView.getSize().y / 2);
	}
	else if (player->GetPosition().x <= tile->GetLocalBounds().left + worldView.getSize().x / 2 &&
		player->GetPosition().y >= tile->GetLocalBounds().height - worldView.getSize().y / 2)
	{
		worldView.setCenter(tile->GetLocalBounds().left + worldView.getSize().x / 2,
			tile->GetLocalBounds().height - worldView.getSize().y / 2);
	}
	//right view
	else if (player->GetPosition().x >= tile->GetLocalBounds().width - worldView.getSize().x / 2 &&
		player->GetPosition().y <= tile->GetLocalBounds().top + worldView.getSize().y / 2)
	{
		worldView.setCenter(tile->GetLocalBounds().width - worldView.getSize().x / 2,
			tile->GetLocalBounds().top + worldView.getSize().y / 2);
	}
	else if (player->GetPosition().x >= tile->GetLocalBounds().width - worldView.getSize().x / 2 &&
		player->GetPosition().y >= tile->GetLocalBounds().height - worldView.getSize().y / 2)
	{
		worldView.setCenter(tile->GetLocalBounds().width - worldView.getSize().x / 2,
			tile->GetLocalBounds().height - worldView.getSize().y / 2);
	}
	//x view
	else if (player->GetPosition().x <= tile->GetLocalBounds().left + worldView.getSize().x / 2)
	{
		worldView.setCenter(tile->GetLocalBounds().left + worldView.getSize().x / 2, player->GetPosition().y);
	}
	else if (player->GetPosition().x >= tile->GetLocalBounds().width - worldView.getSize().x / 2)
	{
		worldView.setCenter(tile->GetLocalBounds().width - worldView.getSize().x / 2, player->GetPosition().y);
	}
	//y view
	else if (player->GetPosition().y <= tile->GetLocalBounds().top + worldView.getSize().y / 2)
	{
		worldView.setCenter(player->GetPosition().x, tile->GetLocalBounds().top + worldView.getSize().y / 2);
	}
	else if (player->GetPosition().y >= tile->GetLocalBounds().height - worldView.getSize().y / 2)
	{
		worldView.setCenter(player->GetPosition().x, tile->GetLocalBounds().height - worldView.getSize().y / 2);
	}
	else
	{
		worldView.setCenter(player->GetPosition().x, player->GetPosition().y);
	}
}
