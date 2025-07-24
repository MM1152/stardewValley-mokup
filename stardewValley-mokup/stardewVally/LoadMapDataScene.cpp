#include "stdafx.h"
#include "LoadMapDataScene.h"

LoadMapDataScene::LoadMapDataScene()
	:Scene(SceneIds::LoadMapTest)
{
}

void LoadMapDataScene::Init()
{
	
	texIds.push_back(GRAPHICS_PATH"³óÀå(º½).bmp");

	
	tile = new TileMap(VertexType::Game);

	AddGameObject(tile);

	Scene::Init();	
}

void LoadMapDataScene::Enter()
{
	va = Utils::LoadMapData(MAP_PATH"map1.csv");

	worldView.setSize(FRAMEWORK.GetWindowSizeF());
	worldView.setCenter({ FRAMEWORK.GetWindowSizeF().x / 2 , FRAMEWORK.GetWindowSizeF().y / 2 });

	uiView.setSize(FRAMEWORK.GetWindowSizeF());
	uiView.setCenter({ FRAMEWORK.GetWindowSizeF().x / 2 , FRAMEWORK.GetWindowSizeF().y / 2 });
	Scene::Enter();
	
	tile->Set(va, Utils::LoadTextureId());

}

void LoadMapDataScene::Exit()
{
	Scene::Exit();
}

void LoadMapDataScene::Update(float dt)
{
	Scene::Update(dt);
}
