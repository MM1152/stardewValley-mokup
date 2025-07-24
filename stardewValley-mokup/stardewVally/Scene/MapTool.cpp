#include "stdafx.h"
#include "MapTool.h"
#include "TileMap.h"
#include "rapidcsv.h"
#include "Button.h"
MapTool::MapTool()
	: Scene(SceneIds::Maptool)
{
}

void MapTool::Init()
{
	fontIds.push_back(FONT_PATH"DOSGothic.ttf");

	mouseRect.setSize({ 10, 10 });
	worldView.setSize(FRAMEWORK.GetWindowSizeF());
	worldView.setCenter({ FRAMEWORK.GetWindowSizeF().x / 2 , FRAMEWORK.GetWindowSizeF().y / 2});

	uiView.setSize(FRAMEWORK.GetWindowSizeF());	
	uiView.setCenter({ FRAMEWORK.GetWindowSizeF().x / 2 , FRAMEWORK.GetWindowSizeF().y / 2 });


	Button* button = new Button(FONT_PATH"DOSGothic.ttf");
	button->SetString("SAVE");
	button->SetTextColor(sf::Color::Black);
	button->SetPosition({FRAMEWORK.GetWindowSizeF().x / 1.3f, FRAMEWORK.GetWindowSizeF().y - 100.f });
	button->onClickFunc = [this]() {
		Utils::SaveMapData("MapData/map1.csv" , drawTile->GetVaData(), drawTile->GetCellCount() , drawTile->GetTextureId());
	};

	texIds.push_back("graphics/≥Û¿Â(∫Ω).bmp");

	tilemap1 = (TileMap*)AddGameObject(new TileMap(VertexType::Palette));
	tilemap1->getIndexFunc = [this](sf::Vector2f* index) {
		texcoor[0] = index[0];
		texcoor[1] = index[1];
		texcoor[2] = index[2];
		texcoor[3] = index[3];

		std::cout << texcoor[0].x << ", " << texcoor[0].y << std::endl;
		std::cout << texcoor[1].x << ", " << texcoor[1].y << std::endl;
		std::cout << texcoor[2].x << ", " << texcoor[2].y << std::endl;
		std::cout << texcoor[3].x << ", " << texcoor[3].y << std::endl;

	};

	gridTile = new TileMap(VertexType::Grid);
	gridTile->sortingOrder = 5;

	drawTile = new TileMap(VertexType::Draw);
	drawTile->setTextCoorFunc = [this]() {
		return texcoor;
	};

	
	AddGameObject(tilemap1);
	AddGameObject(drawTile);
	AddGameObject(gridTile);
	AddGameObject(button);
	Scene::Init();
}

void MapTool::Enter()
{
	Scene::Enter();
	tilemap1->Set({ 24, 25 }, { 16.f, 16.f }, "graphics/≥Û¿Â(∫Ω).bmp");
	gridTile->drawGrid({ 24, 25 }, { 16.f , 16.f });
	drawTile->Set({ 24, 25 }, { 16.f , 16.f });


	tilemap1->SetPosition({FRAMEWORK.GetWindowSizeF().x / 2 + 200.f, FRAMEWORK.GetWindowSizeF().y / 2 - 300.f });
	gridTile->SetPosition({ 300 , 300});
	drawTile->SetPosition({ 300 , 300 });

	drawTile->SetTexture("graphics/≥Û¿Â(∫Ω).bmp");
}

void MapTool::Update(float dt)
{

	Scene::Update(dt);

	mouseRect.setPosition((sf::Vector2f)InputMgr::GetMousePosition());

		
}

void MapTool::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	window.draw(mouseRect);
}
