#include "stdafx.h"
#include "SceneFarm.h"
#include "TileMap.h"
#include "SpriteGo.h"
#include "Player.h"
#include "NpcMgr.h"
#include "Shop.h"
#include "Collider.h"
#include "TimeMoneyUi.h"
#include "Inventory.h"
#include "QuickBar.h"
#include "DialogueBox.h"
#include "DialogueLoader.h"
#include "Crops.h"
#include "InteractionObject.h"
#include "DropItem.h"
#include "SellBox.h"

SceneFarm::SceneFarm()
	: Scene(SceneIds::Farm)
{
}

void SceneFarm::Init()
{
	texIds.push_back(GRAPHICS_PATH"tools.png");
	texIds.push_back(GRAPHICS_PATH"farmer_base.png");
	texIds.push_back(GRAPHICS_PATH"hats.png");
	texIds.push_back("graphics/testC.png");
	texIds.push_back("graphics/shop_bg.png");
	texIds.push_back(INVEN_IMG_PATH"ItemSlot.png");
	texIds.push_back("graphics/uiBox.png");

	//npc
	texIds.push_back("graphics/npcTest.png");
	texIds.push_back("graphics/npcTalk.png");
	texIds.push_back("graphics/pierre_photo.png");

	//shop items
	texIds.push_back("graphics/parsnip_seeds.png");
	texIds.push_back("graphics/cauliflower_seeds.png");
	texIds.push_back("graphics/potato_seeds.png");
	texIds.push_back("graphics/garlic_seeds.png");

	texIds.push_back("graphics/portraitsBox.png");
	texIds.push_back("graphics/Pierre.png");
	texIds.push_back("graphics/itemSlot_bg.png");

	texIds.push_back("graphics/sellbox.png");

	texIds.push_back(INVEN_IMG_PATH"CraftImage.bmp");

	texIds.push_back("graphics/clock.png");
	texIds.push_back("graphics/moneyFont.png");


	fontIds.push_back("fonts/DOSGothic.ttf");
	fontIds.push_back("fonts/Stardew_Valley.ttf");
	fontIds.push_back("fonts/SDMiSaeng.ttf");
	fontIds.push_back("fonts/DungGeunMo.ttf");

	texIds.push_back(INVEN_IMG_PATH"CraftImage.bmp");

	//Map Load
	texIds.push_back(GRAPHICS_PATH"spring.bmp");
	texIds.push_back(GRAPHICS_PATH"building.png");

	//TimeUi
	texIds.push_back("graphics/clock.png");
	texIds.push_back("graphics/moneyFont.png");

	//font
	fontIds.push_back("fonts/DOSGothic.ttf");
	fontIds.push_back("fonts/DungGeunMo.ttf");
	fontIds.push_back("fonts/SDMiSaeng.ttf");
	fontIds.push_back("fonts/Stardew_Valley.ttf");
	

	//crops
	texIds.push_back("graphics/parsnip.png");
	texIds.push_back("graphics/cauliflower.png");
	texIds.push_back("graphics/potato.png");
	texIds.push_back("graphics/garlic.png");

	//dropItem
	texIds.push_back("graphics/springobjects.png");
	texIds.push_back("graphics/potatodrop.png");
	texIds.push_back("graphics/cauliflowerdrop.png");
	texIds.push_back("graphics/garlicdrop.png");
	texIds.push_back("graphics/parsnipdrop.png");

	npc = new NpcMgr("Npc");
	shop = new Shop("shop");
	dialogueBox = new DialogueBox("DialogueBox");
	sellBox = new SellBox("SellBox");

	AddGameObject(sellBox);
	AddGameObject(dialogueBox);
	AddGameObject(shop);
	AddGameObject(npc);

	inventory->SetQuickBar(quickBar);
	timemoney->Setplayer(player);

	shop->SetInventory(inventory);
	shop->SetPlayer(player);
	shop->SetTimeMoeyUi(timemoney);
	//player & npc

	player->SetNpcMgr(npc);
	player->SetInventory(inventory);
	player->SetTimer(timemoney);

	npc->SetPlayer(player);
	npc->SetTimer(timemoney);
	npc->SetInventory(inventory);
	npc->SetDIalogueBox(dialogueBox);

	sellBox->SetInventory(inventory);
	sellBox->SetPlayer(player);
	sellBox->SetTimeMoeyUi(timemoney);


	itemDataMgr::Instance().LoadShopItems("data/shop.json");
	itemDataMgr::Instance().Load("data/item.json");
	DialogueLoader::Instance().LoadFromJson("data/Dialogues.json");
	

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

	npc->setTalkCallBack([this]() {
		const std::string npcName = "Pierre"; 

		if (!dialogueBox->isDialogueShowing())
		{
			dialogueBox->LoadDialogue(npcName);
			dialogueBox->ShowDialogue();
		}
		else
		{
			if (dialogueBox->IsLastLine())
			{
				dialogueBox->CloseDialogue();
			}
			else
			{
				dialogueBox->NextLine();
			}
		}
		});


	tile = new TileMap(VertexType::Game);
	forGround = new TileMap(VertexType::Game);


	AddGameObject(tile);
	AddGameObject(forGround);

	map.Init(tile, forGround);
	map.Load(MAP_PATH"demomap");
	objects = map.CreateObjects();

	// F9 Draw Collider
	drawCollider = true;

	Scene::Init();

	AddGameObject(player);
	AddGameObject(inventory);
	AddGameObject(quickBar);
	AddGameObject(timemoney);

	for (auto obj : objects) {
		AddGameObject(obj);
	}

	inventory->SetSellBox(sellBox);
}

void SceneFarm::Enter()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(true);
	worldView.setSize({ FRAMEWORK.GetWindowSizeF().x / 4, FRAMEWORK.GetWindowSizeF().y / 4 });

	uiView.setSize(FRAMEWORK.GetWindowSizeF());
	uiView.setCenter({ FRAMEWORK.GetWindowSizeF().x / 2 , FRAMEWORK.GetWindowSizeF().y / 2 });

	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	Scene::Enter(); //push_back
	player->SetPosition({ 208.f, 210.f });



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

	forGround->sortingLayer = SortingLayers::Foreground;
	forGround->sortingOrder = 131;

	player->SetMap(&map);
	player->SetSellBox(sellBox);
	player->sortingLayer = SortingLayers::Foreground;
}

void SceneFarm::Exit()
{
	Scene::Exit();
}

void SceneFarm::Update(float dt)
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

	if (player->GetGrowup())
	{
		for (auto it : cropsList)
		{
			it->GrowUp();
		}
		player->SetGrowup(false);
	}
}

void SceneFarm::Draw(sf::RenderWindow& window)
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

void SceneFarm::CenterView()
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

void SceneFarm::AddCrops(Crops* crops)
{
	AddGameObject(crops);
	cropsList.push_back(crops);
	for (auto it : cropsList)
	{
		if (it != nullptr)
		{
			it->SetPlayer(player);
			it->SetInventory(inventory);
			inventory->SetCrops(it);
		}
		for (auto drop : dropitemList)
		{
			it->SetDropItem(drop);
		}
	}
}
void SceneFarm::RemoveCrops(Crops* crops)
{
	crops->SetActive(false);
	cropsList.remove(crops);
}

void SceneFarm::AddDropItem(DropItem* dropitem)
{
	AddGameObject(dropitem);
	dropitemList.push_back(dropitem);
	for (auto it : dropitemList)
	{
		if (it != nullptr)
		{
			it->SetPlayer(player);
			it->SetInventory(inventory);
			inventory->SetDropItem(it);
			for (auto crop : cropsList)
			{
				it->SetCrops(crop);
			}
		}
	}
}

void SceneFarm::RemoveDropItem(DropItem* dropitem)
{
	dropitem->SetActive(false);
	dropitemList.remove(dropitem);
}






