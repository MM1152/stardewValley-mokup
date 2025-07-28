#include "stdafx.h"
#include "SceneTileChangeTest.h"
#include "Player.h"

SceneTileChangeTest::SceneTileChangeTest()
	:Scene(SceneIds::ChangeTile)
{
}

void SceneTileChangeTest::Init()
{
	texIds.push_back(GRAPHICS_PATH"spring.bmp");
	texIds.push_back(GRAPHICS_PATH"building.png");
	texIds.push_back(GRAPHICS_PATH"testC.png");
	tile = new TileMap(VertexType::Game);
	buildTile = new TileMap(VertexType::Game);

	player = new Player();

	AddGameObject(tile);
	AddGameObject(buildTile);
	AddGameObject(player);

	
	Scene::Init();
}

void SceneTileChangeTest::Release()
{
	Scene::Release();
}

void SceneTileChangeTest::Enter()
{
	Scene::Enter();
	worldView.setSize(FRAMEWORK.GetWindowSizeF() * 0.5f);

	map.Load(MAP_PATH"demomap");

	tile->Set(map.GetTextId(0) , map.GetCellDatas(0));
	buildTile->Set(map.GetTextId(1), map.GetCellDatas(1));

	player->SetMap(&map);
	player->SetPosition({ 300,300 });
}

void SceneTileChangeTest::Exit()
{
	Scene::Exit();
}

// 73 74 -> groundTile
// 308 -> groundHoleTile

void SceneTileChangeTest::Update(float dt)
{
	Scene::Update(dt);
	worldView.setCenter(player->GetPosition());

	if (InputMgr::GetKeyDown(sf::Keyboard::F)) {
		int cellIdx = map.GetCellIndex(player->GetPosition(), 0);
		
		CellData changeCellData = map.GetCell(cellIdx, 0);
		std::cout << changeCellData.idx << std::endl;
		if (changeCellData.idx == 25 || changeCellData.idx == 74) {
			changeCellData = map.GetTextureCell(308, 0);

			map.SetCellData(cellIdx, 0, &changeCellData);
			tile->SetCellData(cellIdx, changeCellData);
		}
	}
}

void SceneTileChangeTest::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
