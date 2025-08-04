#include "stdafx.h"
#include "SceneStore.h"
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
#include "DialogueBox.h"
#include "DialogueLoader.h"


SceneStore::SceneStore()
	: Scene(SceneIds::Store)
{
}

void SceneStore::Init()
{
	texIds.push_back("graphics/store.png");
	texIds.push_back("graphics/uitest.png");
	texIds.push_back(INVEN_IMG_PATH"ItemSlot.png");
	texIds.push_back(GRAPHICS_PATH"farmer_base.png");
	texIds.push_back(GRAPHICS_PATH"shirts.png");
	texIds.push_back(GRAPHICS_PATH"hats.png");
	texIds.push_back(GRAPHICS_PATH"tools.png");
	texIds.push_back(GRAPHICS_PATH"springobjects.png");
	texIds.push_back("graphics/parsnip_seeds.png");
	texIds.push_back("graphics/cauliflower_seeds.png");
	texIds.push_back("graphics/potato_seeds.png");
	texIds.push_back("graphics/garlic_seeds.png");

	texIds.push_back("graphics/npcTest.png");
	texIds.push_back("graphics/pierre_photo.png");

	texIds.push_back("graphics/portraitsBox.png");
	texIds.push_back("graphics/Pierre.png");
	texIds.push_back("graphics/itemSlot_bg.png");

	texIds.push_back(INVEN_IMG_PATH"CraftImage.bmp");

	//Map Load
	texIds.push_back(GRAPHICS_PATH"villige.png");
	texIds.push_back(GRAPHICS_PATH"building.png");

	//TimeUi
	texIds.push_back("graphics/clock.png");
	texIds.push_back("graphics/moneyFont.png");

	//font
	fontIds.push_back("fonts/DOSGothic.ttf");

	npc = new NpcMgr("Npc"); //c
	shop = new Shop("shop"); //c
	dialogueBox = new DialogueBox("DialogueBox"); //c

	AddGameObject(shop);
	AddGameObject(npc);

	shop->SetInventory(inventory);
	shop->SetPlayer(player);
	shop->SetTimeMoeyUi(timemoney);

	npc->SetPlayer(player);
	npc->SetTimer(timemoney);
	npc->SetInventory(inventory);
	npc->SetDIalogueBox(dialogueBox);

	inventory->SetQuickBar(quickBar);
	timemoney->Setplayer(player);
	timemoney->Setplayer(player);

	player->SetNpcMgr(npc);
	player->SetInventory(inventory);
	player->SetTimer(timemoney);
	player->SetDialogueBox(dialogueBox);

	itemDataMgr::Instance().LoadShopItems("data/shop.json");
	itemDataMgr::Instance().Load("data/item.json");

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


	// F9 Draw Collider
	Scene::Init();
	AddGameObject(inventory);
	AddGameObject(quickBar);
	AddGameObject(player);
	AddGameObject(timemoney);
	map.Load(MAP_PATH"store");


}

void SceneStore::Enter()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(true);
	worldView.setSize({ FRAMEWORK.GetWindowSizeF().x / 3, FRAMEWORK.GetWindowSizeF().y / 3 });
	uiView.setSize(FRAMEWORK.GetWindowSizeF());
	uiView.setCenter({ FRAMEWORK.GetWindowSizeF().x / 2 , FRAMEWORK.GetWindowSizeF().y / 2 });

	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	Scene::Enter(); //push_back


	tile->Set(map.GetTextId(0), map.GetCellDatas(0));
	forGround->Set(map.GetTextId(1), map.GetCellDatas(1));

	player->SetMap(&map);


	for (auto tri : map.GetTriggers())
	{
		tri->Init();
		tri->SetPlayer(player);
		if (tri->GetType() == TriggerType::Door)
		{
			tri->callback = [this]() {
				player->SetPosition({ 492.f, 250.f });
				SCENE_MGR.ChangeScene(SceneIds::Village);
				};
		}
	}
}

void SceneStore::Exit()
{
	Scene::Exit();
}

void SceneStore::Update(float dt)
{
	Scene::Update(dt);
	worldView.setCenter(player->GetPosition());
	timemoney->SettingMoney(player->GetMoney());
	timemoney->ResetSettingMoney();

	if (InputMgr::GetKeyDown(sf::Keyboard::F9)) {
		drawCollider = !drawCollider;
	}

	for (auto tri : map.GetTriggers()) {
		tri->Update(dt);
	}
}

void SceneStore::Draw(sf::RenderWindow& window)
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