#include "stdafx.h"
#include "SceneVillige.h"
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

SceneVillige::SceneVillige()
	: Scene(SceneIds::Village)
{
}

void SceneVillige::Init()
{
	SOUND_MGR.Load(SoundType::VILLIGE, "sound/villige.mp3");

	texIds.push_back("graphics/spring.bmp");
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
	texIds.push_back("graphics/uiBox.png");

	texIds.push_back("graphics/npcTalk.png");
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
	fontIds.push_back("fonts/DungGeunMo.ttf");
	fontIds.push_back("fonts/SDMiSaeng.ttf");
	fontIds.push_back("fonts/Stardew_Valley.ttf");

	inventory->SetQuickBar(quickBar);
	timemoney->Setplayer(player);
	timemoney->Setplayer(player);
	player->SetNpcMgr(npc);
	player->SetInventory(inventory);
	player->SetTimer(timemoney);
	player->SetDialogueBox(dialogueBox);

	npc = new NpcMgr("Npc");
	dialogueBox = new DialogueBox("DialogueBox");

	AddGameObject(npc);
	AddGameObject(dialogueBox);

	npc->SetPlayer(player);
	npc->SetTimer(timemoney);
	npc->SetInventory(inventory);
	npc->SetDIalogueBox(dialogueBox);
;
	DialogueLoader::Instance().LoadFromJson("data/Dialogues.json");

	const auto& items = itemDataMgr::Instance().GetShopItemList("Pierre's General Store");
	for (const auto& item : items)
	{
		texIds.push_back(item.itemTextureId);
	}

	npc->setTalkCallBack([this]() {
		const std::string npcName = "Pierre";

		if (!dialogueBox->isDialogueShowing())
		{
			dialogueBox->LoadDialogue(npcName);
			dialogueBox->ShowDialogue();

			npc->SetNpcMove(false);
			npc->SetIsTalking(true);

			player->SetIsPlayer(false);


		}
		else
		{
			if (dialogueBox->IsLastLine())
			{
				dialogueBox->CloseDialogue();
				npc->SetNpcMove(true);
				npc->SetIsTalking(false);

				timemoney->ChangeTimer();
				player->SetIsPlayer(true);
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

	// F9 Draw Collider
	Scene::Init();

	AddGameObject(inventory);
	AddGameObject(quickBar);
	AddGameObject(player);
	AddGameObject(timemoney);
	map.Load(MAP_PATH"Villige");
}

void SceneVillige::Enter()
{
	SOUND_MGR.Play(SoundType::VILLIGE);
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
				player->SetPosition({ 700.f, 300.f });
				SCENE_MGR.ChangeScene(SceneIds::Farm);
				SOUND_MGR.Stop(SoundType::VILLIGE);
				};
		}
		if (tri->GetType() == TriggerType::Bed)
		{
			tri->callback = [this]() {
				player->SetPosition({ 95.f, 225.f });
				SCENE_MGR.ChangeScene(SceneIds::Store);
				};
		}
	}
}

void SceneVillige::Exit()
{
	Scene::Exit();
}

void SceneVillige::Update(float dt)
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

void SceneVillige::Draw(sf::RenderWindow& window)
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

void SceneVillige::CenterView()
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