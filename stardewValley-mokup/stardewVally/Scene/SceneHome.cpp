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
#include "SelectDiaLog.h"

SceneHome::SceneHome()
	: Scene(SceneIds::Home)
{
}

void SceneHome::Init()
{
	texIds.push_back("graphics/spring.bmp");
	texIds.push_back("graphics/testC.png");
	texIds.push_back("graphics/uitest.png");
	texIds.push_back(INVEN_IMG_PATH"ItemSlot.png");
	texIds.push_back(GRAPHICS_PATH"farmer_base.png");
	texIds.push_back(GRAPHICS_PATH"hats.png");
	texIds.push_back(GRAPHICS_PATH"shirts.png");
	texIds.push_back(GRAPHICS_PATH"tools.png");
	texIds.push_back(GRAPHICS_PATH"springobjects.png");
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
	

	bedDiaLog = new SelectDiaLog();
	

	bedDiaLog->SetActive(false);
	inventory->SetQuickBar(quickBar);
	timemoney->Setplayer(player);
	timemoney->Setplayer(player);
	player->SetInventory(inventory);
	player->SetTimer(timemoney);

	const auto& items = itemDataMgr::Instance().GetShopItemList("Pierre's General Store");
	for (const auto& item : items)
	{
		texIds.push_back(item.itemTextureId);
	}

	tile = new TileMap(VertexType::Game);
	forGround = new TileMap(VertexType::Game);

	
	
	AddGameObject(bedDiaLog);
	AddGameObject(tile);
	AddGameObject(forGround);

	AddGameObject(inventory);
	AddGameObject(quickBar);
	AddGameObject(player);
	AddGameObject(timemoney);
	// F9 Draw Collider
	Scene::Init();

	map.Load(MAP_PATH"home");


}

void SceneHome::Enter()
{
	SOUND_MGR.Load(SoundType::DOOROPEN , "sound/doorOpen.mp3");


	FRAMEWORK.GetWindow().setMouseCursorVisible(true);

	blackOutEffect.setFillColor(sf::Color(0,0,0,0));
	
	blackOutEffect.setSize(FRAMEWORK.GetWindowSizeF());

	worldView.setSize({ FRAMEWORK.GetWindowSizeF().x / 3, FRAMEWORK.GetWindowSizeF().y / 3});
	uiView.setSize(FRAMEWORK.GetWindowSizeF());
	uiView.setCenter({ FRAMEWORK.GetWindowSizeF().x / 2 , FRAMEWORK.GetWindowSizeF().y / 2 });

	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	Scene::Enter(); //push_back
	tile->Set(map.GetTextId(0), map.GetCellDatas(0));
	forGround->Set(map.GetTextId(1), map.GetCellDatas(1));

	player->SetMap(&map);
	player->SetPosition({ 193.f, 280.f });

	for (auto tri : map.GetTriggers()) {
		tri->Init();
		tri->Reset();
		tri->SetPlayer(player);
		if (tri->GetType() == TriggerType::Door) {
			tri->callback = [this]() {
				SCENE_MGR.ChangeScene(SceneIds::Farm);
				player->SetPosition({ 375.f, 250.f });
				SOUND_MGR.Play(SoundType::DOOROPEN);
				player->SetActive(false);
			};
		}
		if (tri->GetType() == TriggerType::Bed) {
			tri->callback = [this]() {
				bedDiaLog->Show();
				player->SetIsPlayer(false);
			};
		}
	}

	bedDiaLog->returnIdxFunc = [this](int sleep) {
		isSleep = (bool)sleep;

		if (isSleep) {
			player->SetGrowup(true);
		}
		else {
			player->SetIsPlayer(true);
		}
	};
}

void SceneHome::Exit()
{
	Scene::Exit();
}

void SceneHome::Update(float dt)
{
	Scene::Update(dt);
	worldView.setCenter({ 235.f, 230.f });
	timemoney->SettingMoney(player->GetMoney());
	timemoney->ResetSettingMoney();

	if (InputMgr::GetKeyDown(sf::Keyboard::F9)) {
		drawCollider = !drawCollider;
	}

	for (auto tri : map.GetTriggers()) {
		tri->Update(dt);
	}
	SceneClosed(dt);
}

void SceneHome::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	window.setView(uiView);
	window.draw(blackOutEffect);
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

void SceneHome::SceneClosed(float dt)
{
	if (isSleep) {
		if (fadeOut) {
			curDuration -= dt;
			blackOutEffect.setFillColor(sf::Color(0, 0, 0, (int)(255 * (1.0f - (curDuration / maxDuration)))));
		}
		else if (!fadeOut) {
			curDuration += dt;
			blackOutEffect.setFillColor(sf::Color(0, 0, 0, (int)(255 - (255 * (curDuration / maxDuration)))));
		}

		if (curDuration < 0) {
			curDuration = 0;
			fadeOut = false;
		}
		else if (curDuration > maxDuration) {
			curDuration = maxDuration;
			isSleep = false;
			fadeOut = true;
			player->SetIsPlayer(true);
		}
	}
}

