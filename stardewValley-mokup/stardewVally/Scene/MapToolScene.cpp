#include "stdafx.h"
#include "MapToolScene.h"
#include "TileMap.h"
#include "rapidcsv.h"
#include "Button.h"
#include "InputText.h"
int MapToolScene::drawTileIdx = 0;

MapToolScene::MapToolScene()
	: Scene(SceneIds::Maptool)
{
}

void MapToolScene::Init()
{
	fontIds.push_back(FONT_PATH"DOSGothic.ttf");
	texIds.push_back(GRAPHICS_PATH"building.png");
	texIds.push_back("graphics/³óÀå(º½).bmp");

	mouseRect.setSize({ 10, 10 });

	worldView.setSize(FRAMEWORK.GetWindowSizeF());
	worldView.setCenter({ FRAMEWORK.GetWindowSizeF().x / 2 , FRAMEWORK.GetWindowSizeF().y / 2});

	uiView.setSize(FRAMEWORK.GetWindowSizeF());	
	uiView.setCenter({ FRAMEWORK.GetWindowSizeF().x / 2 , FRAMEWORK.GetWindowSizeF().y / 2 });

	dragAreaRect.setFillColor(sf::Color::Transparent);
	dragAreaRect.setOutlineColor(sf::Color::Red);
	dragAreaRect.setOutlineThickness(1.f);
	dragAreaRect.setSize({ 0,0 });
#pragma region Buttons

	Button* deleteBNT = new Button(FONT_PATH"DOSGothic.ttf");
	deleteBNT->SetString("Delete");
	deleteBNT->SetTextColor(sf::Color::Black);
	deleteBNT->SetPosition({ FRAMEWORK.GetWindowSizeF().x / 1.2f , 0 });
	deleteBNT->onClickFunc = [this]() {
		cellData.idx = -1;
		drawCollider = false;
		index = 0;
	};
	deleteBNT->sortingLayer = SortingLayers::UI;

	Button* buildingBNT = new Button(FONT_PATH"DOSGothic.ttf");
	buildingBNT->SetString("Building");
	buildingBNT->SetTextColor(sf::Color::Black);
	buildingBNT->SetPosition({ FRAMEWORK.GetWindowSizeF().x / 1.37f , 0 });
	buildingBNT->onClickFunc = [this]() {
		drawTileIdx = 1;
		drawCollider = false;
		startDrawCollider = false;
		tilemap1->SetTexture(GRAPHICS_PATH"building.png");
		};
	buildingBNT->sortingLayer = SortingLayers::UI;

	Button* tileBNT = new Button(FONT_PATH"DOSGothic.ttf");
	tileBNT->SetString("Tile");
	tileBNT->SetTextColor(sf::Color::Black);
	tileBNT->SetPosition({ FRAMEWORK.GetWindowSizeF().x / 1.5f , 0 });
	tileBNT->onClickFunc = [this]() {
		drawTileIdx = 0;
		drawCollider = false;
		startDrawCollider = false;
		tilemap1->SetTexture("graphics/³óÀå(º½).bmp");
		};
	tileBNT->sortingLayer = SortingLayers::UI;

	Button* saveBNT = new Button(FONT_PATH"DOSGothic.ttf");
	saveBNT->SetString("SAVE");
	saveBNT->SetTextColor(sf::Color::Black);
	saveBNT->SetPosition({ FRAMEWORK.GetWindowSizeF().x / 1.3f, FRAMEWORK.GetWindowSizeF().y - 100.f });
	saveBNT->onClickFunc = [this]() {
		std::cout << "MapData/" + inputText->GetString() + ".csv" << std::endl;
		map.Save("MapData/"+ inputText->GetString() + ".csv", drawTile[0].GetTextureId(), drawTile[0].GetCellDatas(), drawTile[0].GetCellCount());
		map.Save("MapData/" + inputText->GetString() + "forGround.csv", drawTile[1].GetTextureId(), drawTile[1].GetCellDatas(), drawTile[1].GetCellCount());
		map.Save("MapData/" + inputText->GetString() + "collider.csv" , colliders);
		//Utils::SaveMapData("MapData/map1.csv" , drawTile[0].GetVaData(), drawTile[0].GetCellCount() , drawTile[0].GetTextureId());
		//Utils::SaveMapData("MapData/map1_forGround.csv", drawTile[1].GetVaData(), drawTile[1].GetCellCount(), drawTile[1].GetTextureId());
		};
	saveBNT->sortingLayer = SortingLayers::UI;

	Button* colliderBNT = new Button(FONT_PATH"DOSGothic.ttf");
	colliderBNT->SetString("Collider");
	colliderBNT->SetTextColor(sf::Color::Black);
	colliderBNT->SetPosition({ FRAMEWORK.GetWindowSizeF().x / 1.2f , 50.f });
	colliderBNT->onClickFunc = [this]() {
		drawCollider = true;
		index = -1;
		};
	colliderBNT->sortingLayer = SortingLayers::UI;
#pragma endregion

	inputText = new InputText(FONT_PATH"DOSGothic.ttf");
	inputText->SetTextColor(sf::Color::Black);
	inputText->SetPosition({ saveBNT->GetPosition().x - 100.f, saveBNT->GetPosition().y - 50.f});
	tilemap1 = (TileMap*)AddGameObject(new TileMap(VertexType::Palette));
	//tilemap1->getIndexFunc = [this](sf::Vector2f* index) {
	//	texcoor[0] = index[0];
	//	texcoor[1] = index[1];
	//	texcoor[2] = index[2];
	//	texcoor[3] = index[3];
	//};

	gridTile = new TileMap(VertexType::Grid);
	drawTile = new TileMap[3]{ TileMap(VertexType::Draw) ,TileMap(VertexType::Draw) , TileMap(VertexType::Draw) };	

	AddGameObject(tilemap1);
	AddGameObject(saveBNT);
	AddGameObject(buildingBNT);
	AddGameObject(tileBNT);
	AddGameObject(deleteBNT);
	AddGameObject(inputText);
	AddGameObject(colliderBNT);

	Scene::Init();

	drawTile[0].Init();
	drawTile[1].Init();
	drawTile[2].Init();
	gridTile->Init();
}

void MapToolScene::Enter()
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

	tilemap1->SetPosition({FRAMEWORK.GetWindowSizeF().x / 2 + 200.f, FRAMEWORK.GetWindowSizeF().y / 2 - 260.f });
	tilemap1->sortingLayer = SortingLayers::UI;
	gridTile->SetPosition({ 300 , 300});

	drawTile[0].SetPosition({ 300 , 300 });
	drawTile[1].SetPosition({ 300 , 300 });
	drawTile[2].SetPosition({ 300 , 300 });

	drawTile[0].SetTexture("graphics/³óÀå(º½).bmp");
	drawTile[1].SetTexture(GRAPHICS_PATH"building.png");
}

//FIX : ¹öÆ° Å¬¸¯½Ã Rectagle »ý¼ºµÇ´Â ¹ö±× ¼öÁ¤ ÇÊ¿ä
void MapToolScene::Update(float dt)
{
	mouseRect.setPosition((sf::Vector2f)InputMgr::GetMousePosition());
	//drawTile[drawTileIdx].Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Enter)) {
		SCENE_MGR.ChangeScene(SceneIds::LoadMapTest);
	}

	if (InArea(tilemap1, InputMgr::GetMousePosition()) && InputMgr::GetMouseButton(sf::Mouse::Left) && isDragArea) {
		int newX = (int)((int)(InputMgr::GetMousePosition().x - tilemap1->GetPosition().x)) / 16 * 4;
		int newY = (int)((int)(InputMgr::GetMousePosition().y - tilemap1->GetPosition().y)) / 16 * 4;

		if (prevX != newX || newY != prevY) {
			cellDatas.clear();

			prevX = newX;
			prevY = newY;
			
			yRange = newY / 4 - yIndex / 4;
			xRange = newX / 4 - xIndex / 4;
			for (int i = 0; i <= yRange; i++) {
				for (int j = 0; j <= xRange; j++) {
					cellDatas.push_back(tilemap1->GetCellData((index / 4 + j) + (i * tilemap1->GetCellCount().x)));
					std::cout << cellDatas[cellDatas.size() - 1].idx << std::endl;
				}
			}
			std::cout << std::endl;
			dragAreaRect.setSize({ 16.f * ((newX / 4) - (xIndex / 4) + 1), 16.f * ((newY / 4) - (yIndex / 4) + 1) });
		}
	}
	if (InArea(&drawTile[drawTileIdx] , (sf::Vector2i)ScreenToWorld(InputMgr::GetMousePosition())) && index != -1 && InputMgr::GetMouseButton(sf::Mouse::Left)) {		
		xIndex = (int)((int)(ScreenToWorld(InputMgr::GetMousePosition()).x - drawTile->GetPosition().x)) / 16 * 4;
		yIndex = (int)((int)(ScreenToWorld(InputMgr::GetMousePosition()).y - drawTile->GetPosition().y)) / 16 * 4;
		index = xIndex + drawTile[drawTileIdx].GetCellCount().x * yIndex;

		if (cellDatas.size() == 1) {
			drawTile[drawTileIdx].SetCellData(index / 4, cellData);
		}
		else if(cellDatas.size() >= 1){
			int idx = 0;
			for (int i = 0; i <= yRange; i++) {
				for (int j = 0; j <= xRange; j++) {
					if ((index / 4 + j) + (i * drawTile[drawTileIdx].GetCellCount().x) >= drawTile->GetCellCount().x * drawTile->GetCellCount().y) {
						break;
					}
					drawTile[drawTileIdx].SetCellData((index / 4 + j) + (i * drawTile[drawTileIdx].GetCellCount().x), cellDatas[idx++]);
				}
			}
		}
	}
	else if (InArea(tilemap1, InputMgr::GetMousePosition()) && InputMgr::GetMouseButtonDown(sf::Mouse::Left)) {
		cellDatas.clear();
		drawCollider = false;
		isDragArea = true;
		xIndex = (int)((int)(InputMgr::GetMousePosition().x - tilemap1->GetPosition().x)) / 16 * 4;
		yIndex = (int)((int)(InputMgr::GetMousePosition().y - tilemap1->GetPosition().y)) / 16 * 4;
		index = xIndex + tilemap1->GetCellCount().x * yIndex;
			
		prevX = xIndex;
		prevY = yIndex;

		cellData = tilemap1->GetCellData(index / 4);
		
		dragAreaStartPos = cellData.cellPosition[0] + tilemap1->GetPosition();
		dragAreaRect.setSize({ 16, 16 });
		dragAreaRect.setPosition(dragAreaStartPos);

		cellDatas.push_back(tilemap1->GetCellData(index / 4));
	}
	else if(InputMgr::GetMouseButtonDown(sf::Mouse::Left)) {
		index = -1;
		prevX = -1;
		prevY = -1;
		dragAreaRect.setSize({ 0, 0 });
	}

	if (InputMgr::GetMouseButtonUp(sf::Mouse::Left)) {
		isDragArea = false;
	}

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left) && drawCollider) {
		startDrawCollider = true;
		colliders.push_back(new sf::RectangleShape());
		colliders[colliders.size() - 1]->setFillColor(sf::Color::Transparent);
		colliders[colliders.size() - 1]->setOutlineColor(sf::Color::Blue);
		colliders[colliders.size() - 1]->setOutlineThickness(1.f);
		drawColliderStartPos = ScreenToWorld(InputMgr::GetMousePosition());
		colliders[colliders.size() - 1]->setPosition(drawColliderStartPos);
	}
	else if (InputMgr::GetMouseButton(sf::Mouse::Left) && startDrawCollider) {
		sf::RectangleShape& col = *colliders[colliders.size() - 1];
		sf::Vector2f mousePosition = ScreenToWorld(InputMgr::GetMousePosition());
		col.setSize(mousePosition -  drawColliderStartPos);
	}
	else if (InputMgr::GetKey(sf::Keyboard::LControl) && InputMgr::GetKeyDown(sf::Keyboard::Z) && drawCollider){
		if (colliders.size() > 0) {
			delete colliders[colliders.size() - 1];
			colliders.resize(colliders.size() - 1);
		}
	}
	else if (InputMgr::GetMouseButtonUp(sf::Mouse::Left) && drawCollider && startDrawCollider) {
		startDrawCollider = false;
		if (colliders[colliders.size() - 1]->getSize().x == 0 || colliders[colliders.size() - 1]->getSize().y == 0) {
			delete colliders[colliders.size() - 1];
			colliders.resize(colliders.size() - 1);
		}
	}

	DragToMoveScreen(dt);
	Scene::Update(dt);

}

void MapToolScene::Draw(sf::RenderWindow& window)
{
	window.setView(worldView);
	drawTile[0].Draw(window);
	drawTile[1].Draw(window);
	gridTile->Draw(window);
	for (auto col : colliders) {
		window.draw(*col);
	}

	Scene::Draw(window);
	window.draw(mouseRect);

	window.setView(uiView);
	window.draw(dragAreaRect);

	//drawTile[2].Draw();
}

void MapToolScene::Exit()
{
	Scene::Exit();
	for (int i = 0; i < colliders.size(); i++) {
		delete colliders[i];
	}
	colliders.clear();
}

void MapToolScene::DragToMoveScreen(float dt)
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

bool MapToolScene::InArea(TileMap* tile, sf::Vector2i mousePos)
{
	bool left = mousePos.x - (tile->GetLocalBounds().left + tile->GetPosition().x) > 0;
	bool right = mousePos.x - (tile->GetLocalBounds().width + tile->GetPosition().x) < 0;
	bool top = mousePos.y - (tile->GetLocalBounds().top + tile->GetPosition().y) > 0;
	bool height = mousePos.y - (tile->GetLocalBounds().height + tile->GetPosition().y) < 0;

	return left && right && top && height;
}
