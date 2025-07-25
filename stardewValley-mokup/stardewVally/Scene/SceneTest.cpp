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
	worldView.setSize({ FRAMEWORK.GetWindowSizeF().x / 7, FRAMEWORK.GetWindowSizeF().y / 6 });

	uiView.setSize(FRAMEWORK.GetWindowSizeF());
	uiView.setCenter({ FRAMEWORK.GetWindowSizeF().x / 2 , FRAMEWORK.GetWindowSizeF().y / 2 });

	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	Scene::Enter(); //push_back
	map.Load(MAP_PATH"test");


	tile->Set(map.GetTextId(0), map.GetCellData(0));
	forGround->Set(map.GetTextId(1), map.GetCellData(1));

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

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Right))
	{
		std::cout << "player.x : " << player->GetPosition().x << std::endl;
		std::cout << "player.y : " << player->GetPosition().y << std::endl;
		std::cout << "worldView.x : " << worldView.getSize().x << std::endl;
		std::cout << "worldView.y : " << worldView.getSize().y << std::endl;
		std::cout << tile->GetLocalBounds().left << std::endl;
		std::cout << tile->GetLocalBounds().width << std::endl;
		std::cout << tile->GetLocalBounds().top << std::endl;
		std::cout << tile->GetLocalBounds().height << std::endl;

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
