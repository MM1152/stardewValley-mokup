#include "stdafx.h"
#include "LoadMapDataScene.h"

LoadMapDataScene::LoadMapDataScene()
	:Scene(SceneIds::LoadMapTest)
{
}

void LoadMapDataScene::Init()
{
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

	tile->Set(map.GetTextId() ,map.Load(MAP_PATH"map2.csv" , 0));
	forGround->Set(map.GetTextId(), map.Load(MAP_PATH"map2forGround.csv", 1));
	map.Load(MAP_PATH"map2collider.csv");
	
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
	for (auto col : map.GetColliders()) {
		window.draw(*col);
	}
}

void LoadMapDataScene::Update(float dt)
{
	Scene::Update(dt);
}
