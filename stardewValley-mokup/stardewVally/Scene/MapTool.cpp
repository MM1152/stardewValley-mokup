#include "stdafx.h"
#include "MapTool.h"
#include "TileMap.h"

MapTool::MapTool()
	: Scene(SceneIds::Maptool)
{
}

void MapTool::Init()
{
	texIds.push_back("graphics/³óÀå(º½).bmp");

	tilemap1 = (TileMap*)AddGameObject(new TileMap());
	tilemap1->Set({24, 25}, {16.f, 16.f});
	tilemap1->drawGrid({25, 24}, {16.f, 16.f});
	tilemap1->SetId("graphics/³óÀå(º½).bmp");

	Scene::Init();
}

void MapTool::Enter()
{
	Scene::Enter();
	tilemap1->SetPosition({FRAMEWORK.GetWindowSizeF().x / 2 , FRAMEWORK.GetWindowSizeF().y / 2 });

}

void MapTool::Update(float dt)
{
	sf::Vector2i screenPos = InputMgr::GetMousePosition();
	sf::RenderWindow& window = FRAMEWORK.GetWindow();
	sf::Vector2f worldPos = window.mapPixelToCoords(screenPos);

	Scene::Update(dt);

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		tilemap1->GetPosition();
	}
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Right))
	{
		tilemap1->SetPosition(worldPos);
	}


}

