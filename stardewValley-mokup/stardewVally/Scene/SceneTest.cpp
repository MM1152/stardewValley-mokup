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
#include "DialogueBox.h"
#include "DialogueLoader.h"
#include "Crops.h"
#include "DropItem.h"

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
	texIds.push_back("graphics/caluliflower.png");
	texIds.push_back("graphics/potato.png");
	texIds.push_back("graphics/garlic.png");
	texIds.push_back("graphics/garlic_seeds.png");


	inventory = new Inventory(INVEN_IMG_PATH"CraftImage.bmp");
	quickBar = new QuickBar(INVEN_IMG_PATH"CraftImage.bmp");
	npc = new NpcMgr("Npc");
	player = new Player("Player");
	timemoney = new TimeMoneyUi("TimeMoney");
	shop = new Shop("shop");
	dialogueBox = new DialogueBox("DialogueBox");

	AddGameObject(dialogueBox);


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
	npc->SetDIalogueBox(dialogueBox);
	AddGameObject(player);
	AddGameObject(npc);



	itemDataMgr::Instance().LoadShopItems("data/shop.json");

	itemDataMgr::Instance().Load("data/item.json");


	DialogueLoader::Instance().LoadFromJson("data/Dialogues.json");
	
	itemDataMgr::Instance().LoadShopItems("data/shop.json");
	const auto& items = itemDataMgr::Instance().GetShopItemList("Pierre's General Store");
	std::cout << items.size() << std::endl;
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
	// F9 Draw Collider
	drawCollider = true;

	Scene::Init();
}

void SceneTest::Enter()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(true);
	worldView.setSize({ FRAMEWORK.GetWindowSizeF().x / 6, FRAMEWORK.GetWindowSizeF().y / 6 });

	uiView.setSize(FRAMEWORK.GetWindowSizeF());
	uiView.setCenter({ FRAMEWORK.GetWindowSizeF().x / 2 , FRAMEWORK.GetWindowSizeF().y / 2 });

	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	Scene::Enter(); //push_back
	player->SetPosition({ 208.f, 210.f });

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

	forGround->sortingLayer = SortingLayers::Foreground;
	forGround->sortingOrder = 131;

	player->sortingLayer = SortingLayers::Foreground;
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

	if (player->GetGrowup())
	{
		for (auto it : cropsList)
		{
			it->GrowUp();
		}
		player->SetGrowup(false);

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

void SceneTest::AddCrops(Crops* crops)
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

void SceneTest::RemoveCrops(Crops* crops)
{
	crops->SetActive(false);
	cropsList.remove(crops);
}

std::list<Crops*> SceneTest::GetCropsList()
{
	return cropsList;
}

Crops* SceneTest::GetRemoveCrops(std::list<Crops*> cropslist)
{
	for (auto it : cropslist)
	{
		return it;
	}
}

void SceneTest::AddDropItem(DropItem* dropitem)
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
		}
	}
}


