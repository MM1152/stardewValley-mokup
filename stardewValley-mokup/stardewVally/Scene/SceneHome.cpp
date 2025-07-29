#include "stdafx.h"
#include "SceneHome.h"
#include "TileMap.h"
#include "SpriteGo.h"
#include "Player.h"
#include "NpcMgr.h"
#include "Shop.h"
#include "Collider.h"
#include "TimeMoneyUi.h"
#include "Inventory.h"
#include "QuickBar.h"
#include "Map.h"
SceneHome::SceneHome()
	: Scene(SceneIds::Home)
{
}

void SceneHome::Init()
{
	texIds.push_back("graphics/testC.png");
	texIds.push_back("graphics/uitest.png");
	texIds.push_back(INVEN_IMG_PATH"ItemSlot.png");
	texIds.push_back(GRAPHICS_PATH"farmer_base.png");

	texIds.push_back("graphics/parsnip_seeds.png");
	texIds.push_back("graphics/cauliflower_seeds.png");
	texIds.push_back("graphics/potato_seeds.png");
	texIds.push_back("graphics/garlic_seeds.png");

	texIds.push_back("graphics/portraitsBox.png");
	texIds.push_back("graphics/Pierre.png");
	texIds.push_back("graphics/itemSlot_bg.png");

	texIds.push_back(INVEN_IMG_PATH"CraftImage.bmp");

	//Map Load
	texIds.push_back(GRAPHICS_PATH"home.png");
	texIds.push_back(GRAPHICS_PATH"building.png");

	//TimeUi
	texIds.push_back("graphics/clock.png");
	texIds.push_back("graphics/moneyFont.png");

	//font
	fontIds.push_back("fonts/DOSGothic.ttf");


	inventory = new Inventory(INVEN_IMG_PATH"CraftImage.bmp");
	quickBar = new QuickBar(INVEN_IMG_PATH"CraftImage.bmp");
	player = new Player("Player");
	timemoney = new TimeMoneyUi("TimeMoney");

	AddGameObject(inventory);
	AddGameObject(quickBar);
	inventory->SetQuickBar(quickBar);

	//TimeMoney

	timemoney->Setplayer(player);
	AddGameObject(timemoney);

	//player
	player->SetInventory(inventory);
	player->SetTimer(timemoney);
	AddGameObject(player);



	const auto& items = itemDataMgr::Instance().GetShopItemList("Pierre's General Store");

	for (const auto& item : items)
	{
		texIds.push_back(item.itemTextureId);
	}

	tile = new TileMap(VertexType::Game);
	forGround = new TileMap(VertexType::Game);
	AddGameObject(tile);
	AddGameObject(forGround);


	// F9 Draw Collider
	drawCollider = true;

	Scene::Init();
	
}

void SceneHome::Enter()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(true);
	worldView.setSize({ FRAMEWORK.GetWindowSizeF().x / 3, FRAMEWORK.GetWindowSizeF().y / 3});
	uiView.setSize(FRAMEWORK.GetWindowSizeF());
	uiView.setCenter({ FRAMEWORK.GetWindowSizeF().x / 2 , FRAMEWORK.GetWindowSizeF().y / 2 });

	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	Scene::Enter(); //push_back
	map.Load(MAP_PATH"home");

	for (auto tri : map.GetTriggers()) {
		tri->Init();
		tri->SetPlayer(player);
		if (tri->GetType() == TriggerType::Door) {
			tri->callback = [this]() {
				SCENE_MGR.ChangeScene(SceneIds::Test);
			};
		}
	}

	tile->Set(map.GetTextId(0), map.GetCellDatas(0));
	forGround->Set(map.GetTextId(1), map.GetCellDatas(1));

	player->SetMap(&map);
	player->SetPosition({ 200.f, 280.f });

}

void SceneHome::Exit()
{
	Scene::Exit();
	map.Release();
}

void SceneHome::Update(float dt)
{
	Scene::Update(dt);
	worldView.setCenter({ 250.f, 230.f });
	timemoney->SettingMoney(player->GetMoney());
	timemoney->ResetSettingMoney();

	if (InputMgr::GetKeyDown(sf::Keyboard::F9)) {
		drawCollider = !drawCollider;
	}

	for (auto tri : map.GetTriggers()) {
		tri->Update(dt);
	}
}

void SceneHome::Draw(sf::RenderWindow& window)
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