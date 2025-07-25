#include "stdafx.h"
#include "LoadMapDataScene.h"

LoadMapDataScene::LoadMapDataScene()
	:Scene(SceneIds::LoadMapTest)
{
}

void LoadMapDataScene::Init()
{
	drawCollider = true;
	texIds.push_back(GRAPHICS_PATH"³óÀå(º½).bmp");
	texIds.push_back(GRAPHICS_PATH"building.png");

	tile = new TileMap(VertexType::Game);
	forGround = new TileMap(VertexType::Game);

	AddGameObject(tile);
	AddGameObject(forGround);
	Scene::Init();	
}

void LoadMapDataScene::Enter()
{
	worldView.setSize(FRAMEWORK.GetWindowSizeF());
	worldView.setCenter({ FRAMEWORK.GetWindowSizeF().x / 2 , FRAMEWORK.GetWindowSizeF().y / 2 });

	uiView.setSize(FRAMEWORK.GetWindowSizeF());
	uiView.setCenter({ FRAMEWORK.GetWindowSizeF().x / 2 , FRAMEWORK.GetWindowSizeF().y / 2 });
	Scene::Enter();

	map.Load(MAP_PATH"map2");

	tile->Set(map.GetTextId(0), map.GetCellData(0));
	forGround->Set(map.GetTextId(1), map.GetCellData(1));
	
	//tile->Set(va, Utils::LoadTextureId());

}

void LoadMapDataScene::Exit()
{
	Scene::Exit();
	map.Release();
}

void LoadMapDataScene::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	if (drawCollider) {
		for (auto col : map.GetColliders()) {
			window.draw(*col);
		}
	}
	
}

void LoadMapDataScene::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::F9)) {
		drawCollider = !drawCollider;
	}
}
