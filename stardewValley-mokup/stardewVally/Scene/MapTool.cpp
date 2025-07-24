#include "stdafx.h"
#include "MapTool.h"
#include "TileMap.h"
#include "rapidcsv.h"
#include "Button.h"

int MapTool::drawTileIdx = 0;

MapTool::MapTool()
	: Scene(SceneIds::Maptool)
{
}

void MapTool::Init()
{
	fontIds.push_back(FONT_PATH"DOSGothic.ttf");
	texIds.push_back(GRAPHICS_PATH"building.png");
	texIds.push_back("graphics/³óÀå(º½).bmp");

	mouseRect.setSize({ 10, 10 });

	worldView.setSize(FRAMEWORK.GetWindowSizeF());
	worldView.setCenter({ FRAMEWORK.GetWindowSizeF().x / 2 , FRAMEWORK.GetWindowSizeF().y / 2});

	uiView.setSize(FRAMEWORK.GetWindowSizeF());	
	uiView.setCenter({ FRAMEWORK.GetWindowSizeF().x / 2 , FRAMEWORK.GetWindowSizeF().y / 2 });

	Button* deleteBNT = new Button(FONT_PATH"DOSGothic.ttf");
	deleteBNT->SetString("Delete");
	deleteBNT->SetTextColor(sf::Color::Black);
	deleteBNT->SetPosition({ FRAMEWORK.GetWindowSizeF().x / 1.15f , 0 });
	deleteBNT->onClickFunc = [this]() {
		texcoor[0] = { 0,0 };
		texcoor[1] = { 0,0 };
		texcoor[2] = { 0,0 };
		texcoor[3] = { 0,0 };
		};
	deleteBNT->sortingLayer = SortingLayers::UI;

	Button* buildingBNT = new Button(FONT_PATH"DOSGothic.ttf");
	buildingBNT->SetString("BUILDING");
	buildingBNT->SetTextColor(sf::Color::Black);
	buildingBNT->SetPosition({FRAMEWORK.GetWindowSizeF().x / 1.3f , 0});
	buildingBNT->onClickFunc = [this]() {
		drawTileIdx = 1;
		tilemap1->SetTexture(GRAPHICS_PATH"building.png");
	};
	buildingBNT->sortingLayer = SortingLayers::UI;

	Button* tileBNT = new Button(FONT_PATH"DOSGothic.ttf");
	tileBNT->SetString("Tile");
	tileBNT->SetTextColor(sf::Color::Black);
	tileBNT->SetPosition({ FRAMEWORK.GetWindowSizeF().x / 1.5f , 0 });
	tileBNT->onClickFunc = [this]() {
		drawTileIdx = 0;
		tilemap1->SetTexture("graphics/³óÀå(º½).bmp");
	};
	tileBNT->sortingLayer = SortingLayers::UI;

	Button* saveBNT = new Button(FONT_PATH"DOSGothic.ttf");
	saveBNT->SetString("SAVE");
	saveBNT->SetTextColor(sf::Color::Black);
	saveBNT->SetPosition({FRAMEWORK.GetWindowSizeF().x / 1.3f, FRAMEWORK.GetWindowSizeF().y - 100.f });
	saveBNT->onClickFunc = [this]() {
		Utils::SaveMapData("MapData/map1.csv" , drawTile[0].GetVaData(), drawTile[0].GetCellCount() , drawTile[0].GetTextureId());
		Utils::SaveMapData("MapData/map1_forGround.csv", drawTile[0].GetVaData(), drawTile[0].GetCellCount(), drawTile[0].GetTextureId());
	};
	saveBNT->sortingLayer = SortingLayers::UI;

	tilemap1 = (TileMap*)AddGameObject(new TileMap(VertexType::Palette));
	
	tilemap1->getIndexFunc = [this](sf::Vector2f* index) {
		texcoor[0] = index[0];
		texcoor[1] = index[1];
		texcoor[2] = index[2];
		texcoor[3] = index[3];
	};

	gridTile = new TileMap(VertexType::Grid);
	
	drawTile = new TileMap[3]{ TileMap(VertexType::Draw) ,TileMap(VertexType::Draw) , TileMap(VertexType::Draw) };
	for (int i = 0; i < 3; i++) {
		drawTile[i].setTextCoorFunc = [this]() {
			return texcoor;
		};
		drawTile[i].SetScene(this);
	}
	
	

	AddGameObject(tilemap1);
	AddGameObject(saveBNT);
	AddGameObject(buildingBNT);
	AddGameObject(tileBNT);
	AddGameObject(deleteBNT);
	Scene::Init();

	drawTile[0].Init();
	drawTile[1].Init();
	drawTile[2].Init();
	gridTile->Init();
}

void MapTool::Enter()
{
	drawTile[0].Reset();
	drawTile[1].Reset();
	drawTile[2].Reset();
	gridTile->Reset();
	Scene::Enter();
	tilemap1->Set({ 24, 25 }, { 16.f, 16.f }, "graphics/³óÀå(º½).bmp");
	gridTile->drawGrid({ 24, 25 }, { 16.f , 16.f });
	drawTile[0].Set({ 24, 25 }, { 16.f , 16.f });
	drawTile[1].Set({ 24, 25 }, { 16.f , 16.f });
	drawTile[2].Set({ 24, 25 }, { 16.f , 16.f });

	tilemap1->SetPosition({FRAMEWORK.GetWindowSizeF().x / 2 + 200.f, FRAMEWORK.GetWindowSizeF().y / 2 - 200.f });
	tilemap1->sortingLayer = SortingLayers::UI;
	gridTile->SetPosition({ 300 , 300});

	drawTile[0].SetPosition({ 300 , 300 });
	drawTile[1].SetPosition({ 300 , 300 });
	drawTile[2].SetPosition({ 300 , 300 });

	drawTile[0].SetTexture("graphics/³óÀå(º½).bmp");
	drawTile[1].SetTexture(GRAPHICS_PATH"building.png");
}

void MapTool::Update(float dt)
{

	Scene::Update(dt);

	mouseRect.setPosition((sf::Vector2f)InputMgr::GetMousePosition());

	drawTile[drawTileIdx].Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Enter)) {
		SCENE_MGR.ChangeScene(SceneIds::LoadMapTest);
	}

	

	DragToMoveScreen(dt);
}

void MapTool::Draw(sf::RenderWindow& window)
{
	window.setView(worldView);
	drawTile[0].Draw(window);
	drawTile[1].Draw(window);
	gridTile->Draw(window);
	Scene::Draw(window);
	window.draw(mouseRect);


	//drawTile[2].Draw();
}

void MapTool::Exit()
{
	Scene::Exit();
}

void MapTool::DragToMoveScreen(float dt)
{
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Right)) {
		dragStartPos = (sf::Vector2f)InputMgr::GetMousePosition();
	}
	if (InputMgr::GetMouseButton(sf::Mouse::Right)) {
		worldView.setCenter({ worldView.getCenter() - ((sf::Vector2f)InputMgr::GetMousePosition() - dragStartPos) * dt * 5.f });
	}
	if (InputMgr::GetMouseWheel() != 0) {
		float heightPer = worldView.getSize().y / worldView.getSize().x;
		worldView.setSize({ worldView.getSize().x - 50.f * InputMgr::GetMouseWheel(),worldView.getSize().y - (50.f * InputMgr::GetMouseWheel() * heightPer) });
	}
}