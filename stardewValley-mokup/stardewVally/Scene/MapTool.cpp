#include "stdafx.h"
#include "MapTool.h"
#include "TileMap.h"

MapTool::MapTool()
	: Scene(SceneIds::Maptool)
{
}

void MapTool::Init()
{
	worldView.setSize(FRAMEWORK.GetWindowSizeF());
	worldView.setCenter({ FRAMEWORK.GetWindowSizeF().x / 4 , FRAMEWORK.GetWindowSizeF().y / 2});
	texIds.push_back("graphics/³óÀå(º½).bmp");
	tilemap1 = (TileMap*)AddGameObject(new TileMap());
	tilemap1->SetType(TileMap::ToolType::Farm_spring);

	Scene::Init();
}

void MapTool::Enter()
{
	Scene::Enter();
	tilemap1->SetPosition({FRAMEWORK.GetWindowSizeF().x / 2 , FRAMEWORK.GetWindowSizeF().y / 2 });
}

void MapTool::Update(float dt)
{
	Scene::Update(dt);
}