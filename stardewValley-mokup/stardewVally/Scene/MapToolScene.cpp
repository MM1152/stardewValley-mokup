#include "stdafx.h"
#include "MapToolScene.h"
#include "TileMap.h"
#include "rapidcsv.h"
#include "Button.h"
#include "InputText.h"
#include "Trigger.h"

int MapToolScene::drawTileIdx = 0;

MapToolScene::MapToolScene()
	: Scene(SceneIds::Maptool)
{
}

void MapToolScene::Init()
{
	///map
	fontIds.push_back(FONT_PATH"DOSGothic.ttf");
	texIds.push_back(GRAPHICS_PATH"building.png");
	texIds.push_back("graphics/spring.bmp");
	texIds.push_back("graphics/home.png");
	texIds.push_back("graphics/stroe.png");
	texIds.push_back(GRAPHICS_PATH"springobjects.png");

	//button
	texIds.push_back("title/object.png");
	texIds.push_back("title/building.png");
	texIds.push_back("title/collider.png");
	texIds.push_back("title/gotitle.png");
	texIds.push_back("title/load.png");
	texIds.push_back("title/save.png");
	texIds.push_back("title/yes.png");
	texIds.push_back("title/no.png");
	texIds.push_back("title/gotitleyes_or_no.png");
	texIds.push_back("title/tile.png");
	texIds.push_back("title/trigger.png");
	texIds.push_back("title/delete.png");
	texIds.push_back("title/gotitle.png");


	mouseRect.setSize({ 10, 10 });

	worldView.setSize(FRAMEWORK.GetWindowSizeF());
	worldView.setCenter({ FRAMEWORK.GetWindowSizeF().x / 2 , FRAMEWORK.GetWindowSizeF().y / 2 });

	uiView.setSize(FRAMEWORK.GetWindowSizeF());
	uiView.setCenter({ FRAMEWORK.GetWindowSizeF().x / 2 , FRAMEWORK.GetWindowSizeF().y / 2 });

	dragAreaRect.setFillColor(sf::Color::Transparent);
	dragAreaRect.setOutlineColor(sf::Color::Red);
	dragAreaRect.setOutlineThickness(1.f);
	dragAreaRect.setSize({ 0,0 });

	gotitleyes_or_no.setScale({ 1.3f, 1.3f });
	gotitleyes_or_no.setPosition({ 375.f, 200.f });

#pragma region Buttons

	triggerTypeButton.push_back(new Button(FONT_PATH"DOSGothic.ttf"));
	triggerTypeButton.push_back(new Button(FONT_PATH"DOSGothic.ttf"));

	triggerTypeButton[0]->SetTextColor(sf::Color::Black);
	triggerTypeButton[0]->SetPosition({ FRAMEWORK.GetWindowSizeF().x / 2.f , FRAMEWORK.GetWindowSizeF().y / 2.f });
	triggerTypeButton[0]->onClickFunc = [this]() {
		if (!gotitleview)
		{
			triggers[triggers.size() - 1]->SetType(TriggerType::Door);
			isShowTriggerBox = false;
			drawTrigger = false;
		}
		};
	triggerTypeButton[1]->SetTextColor(sf::Color::Black);
	triggerTypeButton[1]->SetPosition({ FRAMEWORK.GetWindowSizeF().x * 0.6f , FRAMEWORK.GetWindowSizeF().y / 2.f });
	triggerTypeButton[1]->onClickFunc = [this]() {
		if (!gotitleview)
		{
			triggers[triggers.size() - 1]->SetType(TriggerType::Bed);
			isShowTriggerBox = false;
			drawTrigger = false;
		}
		};

	// buttons
	objects = new Button(FONT_PATH"DOSGothic.ttf", "title/object.png");
	objects->SetString("        ");
	objects->SetScale({ 1.f, 1.2f });
	objects->SetPosition({ FRAMEWORK.GetWindowSizeF().x / 1.37f, 50.f });
	objects->onClickFunc = [this]() {
		if (!gotitleview)
		{
			drawTileIdx = 2;
			drawTrigger = false;
			drawCollider = false;
			startDraw = false;
			tilemap1->SetTexture(GRAPHICS_PATH"springobjects.png");
		}
		};
	objects->sortingLayer = SortingLayers::UI;

	triggerButton = new Button(FONT_PATH"DOSGothic.ttf", "title/trigger.png");
	triggerButton->SetString("        ");
	triggerButton->SetScale({ 1.f, 1.2f });
	triggerButton->SetPosition({ FRAMEWORK.GetWindowSizeF().x / 1.6f, 50.f });
	triggerButton->onClickFunc = [this]() {
		if (!gotitleview)
		{
			drawTrigger = true;
			drawCollider = false;
			startDraw = false;
		}
		};
	triggerButton->sortingLayer = SortingLayers::UI;
	AddGameObject(triggerButton);


	deleteBNT = new Button(FONT_PATH"DOSGothic.ttf", "title/delete.png");
	deleteBNT->SetString("        ");
	deleteBNT->SetScale({ 1.f, 1.2f });
	deleteBNT->SetPosition({ FRAMEWORK.GetWindowSizeF().x / 1.2f , 0 });
	deleteBNT->onClickFunc = [this]() {
		if (!gotitleview)
		{
			cellData.idx = -1;
			drawTrigger = false;
			drawCollider = false;
			startDraw = false;
			index = 0;
		}
		};
	deleteBNT->sortingLayer = SortingLayers::UI;

	buildingBNT = new Button(FONT_PATH"DOSGothic.ttf", "title/building.png");
	buildingBNT->SetString("        ");
	buildingBNT->SetScale({ 1.f, 1.2f });
	buildingBNT->SetPosition({ FRAMEWORK.GetWindowSizeF().x / 1.37f , 0 });
	buildingBNT->onClickFunc = [this]() {
		if (!gotitleview)
		{
			drawTileIdx = 1;
			drawTrigger = false;
			drawCollider = false;
			startDraw = false;
			tilemap1->SetTexture(GRAPHICS_PATH"building.png");
		}
		};
	buildingBNT->sortingLayer = SortingLayers::UI;

	tileBNT = new Button(FONT_PATH"DOSGothic.ttf", "title/tile.png");
	tileBNT->SetString("        ");
	tileBNT->SetScale({ 1.f, 1.2f });
	tileBNT->SetPosition({ FRAMEWORK.GetWindowSizeF().x / 1.6f , 0 });
	tileBNT->onClickFunc = [this]() {
		if (!gotitleview)
		{
			drawTileIdx = 0;
			drawCollider = false;
			startDraw = false;
			//change here1/3 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			tilemap1->SetTexture("graphics/spring.bmp");
		}
		};
	tileBNT->sortingLayer = SortingLayers::UI;

	saveBNT = new Button(FONT_PATH"DOSGothic.ttf", "title/save.png");
	saveBNT->SetString("        ");
	saveBNT->SetScale({ 1.f, 1.2f });
	saveBNT->SetPosition({ FRAMEWORK.GetWindowSizeF().x / 1.37f, FRAMEWORK.GetWindowSizeF().y - 100.f });
	saveBNT->onClickFunc = [this]() {
		if (!gotitleview)
		{
			std::cout << "MapData/" + inputText->GetString() + ".csv" << std::endl;
			map.Save("MapData/" + inputText->GetString() + ".csv", drawTile[0].GetTextureId(), drawTile[0].GetCellDatas(), drawTile[0].GetCellCount());
			map.Save("MapData/" + inputText->GetString() + "forGround.csv", drawTile[1].GetTextureId(), drawTile[1].GetCellDatas(), drawTile[1].GetCellCount());
			map.Save("MapData/" + inputText->GetString() + "objects.csv", drawTile[2].GetTextureId(), drawTile[2].GetCellDatas(), drawTile[2].GetCellCount());
			map.Save("MapData/" + inputText->GetString() + "collider.csv", colliders);
			map.Save("MapData/" + inputText->GetString() + "trigger.csv", triggers);
		}

		//Utils::SaveMapData("MapData/map1.csv" , drawTile[0].GetVaData(), drawTile[0].GetCellCount() , drawTile[0].GetTextureId());
		//Utils::SaveMapData("MapData/map1_forGround.csv", drawTile[1].GetVaData(), drawTile[1].GetCellCount(), drawTile[1].GetTextureId());
		};
	saveBNT->sortingLayer = SortingLayers::UI;

	loadBNT = new Button(FONT_PATH"DOSGothic.ttf", "title/load.png");
	loadBNT->SetString("        ");
	loadBNT->SetScale({ 1.f, 1.2f });
	loadBNT->SetPosition({ FRAMEWORK.GetWindowSizeF().x / 1.6f, FRAMEWORK.GetWindowSizeF().y - 100.f });
	loadBNT->onClickFunc = [this]() {
		if (!gotitleview) {
			std::string filePath = Utils::OpenFileDialog();
			if (filePath.empty()) return;
			std::vector<std::string> sliceMapFilePath = Utils::Split(filePath, '.');
			std::vector<std::string> sliceMapId = Utils::Split(sliceMapFilePath[0], '\\');
			std::string mapFilePath = MAP_PATH + sliceMapId[sliceMapId.size() - 1];
			std::string mapId = sliceMapId[sliceMapId.size() - 1];

			map.Load(mapFilePath);
			inputText->SetString(mapId, true);

			drawTile[0].Set(map.GetTextId(0), map.GetCellDatas(0));
			drawTile[1].Set(map.GetTextId(1), map.GetCellDatas(1));
			drawTile[2].Set(map.GetTextId(2), map.GetCellDatas(2));
			colliders.clear();
			colliders = map.GetColliders();

			for (auto collider : colliders) {
				collider->setPosition({ collider->getPosition().x + 300.f , collider->getPosition().y + 300.f });
			}
			triggers.clear();
			triggers = map.GetTriggers();
			for (auto trigger : triggers) {
				trigger->SetPosition({ trigger->GetPosition().x + 300.f , trigger->GetPosition().y + 300.f });
			}
		}
		};
	loadBNT->sortingLayer = SortingLayers::UI;

	colliderBNT = new Button(FONT_PATH"DOSGothic.ttf", "title/collider.png");
	colliderBNT->SetString("        ");
	colliderBNT->SetScale({ 1.f, 1.2f });
	colliderBNT->SetPosition({ FRAMEWORK.GetWindowSizeF().x / 1.2f , 50.f });
	colliderBNT->onClickFunc = [this]() {
		if (!gotitleview)
		{
			drawCollider = true;
			drawTrigger = false;
			index = -1;
		}
		};
	colliderBNT->sortingLayer = SortingLayers::UI;

	gotitleBNT = new Button(FONT_PATH"DOSGothic.ttf", "title/gotitle.png");
	gotitleBNT->SetString("        ");
	gotitleBNT->SetScale({ 1.f, 1.2f });
	gotitleBNT->SetPosition({ FRAMEWORK.GetWindowSizeF().x / 1.2f, FRAMEWORK.GetWindowSizeF().y - 100.f });
	gotitleBNT->onClickFunc = [this]() {
		if (!gotitleview)
		{
			gotitleview = true;
		}
		};
	gotitleBNT->sortingLayer = SortingLayers::UI;

	gtyesBNT = new Button("fonts/DOSGothic.ttf", "title/yes.png", "yes");
	gtyesBNT->SetString("         ");
	gtyesBNT->SetScale({ 1.1f, 2.33f });
	gtyesBNT->SetPosition({ 462.f, 415.f });
	gtyesBNT->onClickFunc = [this]() {
		if (gotitleview)
		{
			gotitleview = false;
			SCENE_MGR.ChangeScene(SceneIds::Title);
		}
		};
	gtyesBNT->sortingLayer = SortingLayers::UI;

	gtnoBNT = new Button("fonts/DOSGothic.ttf", "title/no.png", "no");
	gtnoBNT->SetString("         ");
	gtnoBNT->SetScale({ 1.1f, 2.33f });
	gtnoBNT->SetPosition({ 679.f, 415.f });
	gtnoBNT->onClickFunc = [this]() {
		if (gotitleview)
		{
			gotitleview = false;
		}
		};
	gtnoBNT->sortingLayer = SortingLayers::UI;

#pragma endregion

	inputText = new InputText(FONT_PATH"DOSGothic.ttf");
	inputText->SetTextColor(sf::Color::Black);
	inputText->SetPosition({ saveBNT->GetPosition().x - 100.f, saveBNT->GetPosition().y - 50.f });
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
	AddGameObject(objects);
	AddGameObject(loadBNT);

	AddGameObject(gotitleBNT);
	AddGameObject(gtyesBNT);
	AddGameObject(gtnoBNT);

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
	//change here2/3 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	// ++ si add tile here <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	tilemap1->Set({ 24, 25 }, { 16.f, 16.f }, "graphics/spring.bmp");
	gridTile->drawGrid({ 30, 30 }, { 16.f , 16.f });
	drawTile[0].Set({ 30, 30 }, { 16.f , 16.f });
	drawTile[1].Set({ 30, 30 }, { 16.f , 16.f });
	drawTile[2].Set({ 30, 30 }, { 16.f , 16.f });

	//
	tilemap1->SetPosition({ FRAMEWORK.GetWindowSizeF().x / 2 + 200.f, FRAMEWORK.GetWindowSizeF().y / 2 - 260.f });
	tilemap1->sortingLayer = SortingLayers::UI;
	gridTile->SetPosition({ 300 , 300 });

	drawTile[0].SetPosition({ 300 , 300 });
	drawTile[1].SetPosition({ 300 , 300 });
	drawTile[2].SetPosition({ 300 , 300 });

	//change here3/3 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	drawTile[0].SetTexture("graphics/spring.bmp");
	drawTile[1].SetTexture(GRAPHICS_PATH"building.png");
	drawTile[2].SetTexture(GRAPHICS_PATH"springobjects.png");

	for (auto tri : triggerTypeButton) {
		tri->Reset();
	}

	triggerTypeButton[0]->SetString("Door");
	triggerTypeButton[1]->SetString("Bed");

	gotitleyes_or_no.setTexture(TEXTURE_MGR.Get("title/gotitleyes_or_no.png"));
}

//FIX : 버튼 클릭시 Rectagle 생성되는 버그 수정 필요
void MapToolScene::Update(float dt)
{
	mouseRect.setPosition((sf::Vector2f)InputMgr::GetMousePosition());
	//drawTile[drawTileIdx].Update(dt);
	if (!isShowTriggerBox) {
		SelectTile();
		DrawTile();
		DrawColliderBox();
		DrawTriggerBox();
	}

	if (isShowTriggerBox) {
		for (auto tri : triggerTypeButton) {
			tri->Update(dt);
		}
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Enter)) {
		SCENE_MGR.ChangeScene(SceneIds::ChangeTile);
	}

	if (InputMgr::GetMouseButtonUp(sf::Mouse::Left)) {
		isDragArea = false;
	}

	DragToMoveScreen(dt);
	if (!gotitleview)
	{
		gtyesBNT->SetActive(false);
		gtnoBNT->SetActive(false);
	}
	else
	{
		gtyesBNT->SetActive(true);
		gtnoBNT->SetActive(true);
	}
	Scene::Update(dt);
	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		gotitleview = false;
	}
	
}

void MapToolScene::Draw(sf::RenderWindow& window)
{
	window.setView(worldView);
	drawTile[0].Draw(window);
	drawTile[1].Draw(window);
	drawTile[2].Draw(window);
	gridTile->Draw(window);
	for (auto col : colliders) {
		window.draw(*col);
	}
	for (auto tri : triggers) {
		tri->Draw(window);
	}


	Scene::Draw(window);
	window.draw(mouseRect);

	window.setView(uiView);
	window.draw(dragAreaRect);
	if (isShowTriggerBox) {
		for (auto type : triggerTypeButton) {
			type->Draw(window);
		}
	}

	if (gotitleview)
	{
		window.draw(gotitleyes_or_no);
		gtyesBNT->Draw(window);
		gtnoBNT->Draw(window);
	}

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

void MapToolScene::SelectTile()
{
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
				}
			}
			dragAreaRect.setSize({ 16.f * ((newX / 4) - (xIndex / 4) + 1), 16.f * ((newY / 4) - (yIndex / 4) + 1) });
		}
	}

}

void MapToolScene::DrawTile()
{
	if (InArea(&drawTile[drawTileIdx], (sf::Vector2i)ScreenToWorld(InputMgr::GetMousePosition())) && index != -1 && InputMgr::GetMouseButton(sf::Mouse::Left)) {
		xIndex = (int)((int)(ScreenToWorld(InputMgr::GetMousePosition()).x - drawTile->GetPosition().x)) / 16 * 4;
		yIndex = (int)((int)(ScreenToWorld(InputMgr::GetMousePosition()).y - drawTile->GetPosition().y)) / 16 * 4;
		index = xIndex + drawTile[drawTileIdx].GetCellCount().x * yIndex;

		if (cellDatas.size() == 1) {
			drawTile[drawTileIdx].SetCellData(index / 4, cellData);
		}
		else if (cellDatas.size() >= 1) {
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

		std::cout << index / 4 << std::endl;
		std::cout << cellData.cellTextCoord << std::endl;
		prevX = xIndex;
		prevY = yIndex;

		cellData = tilemap1->GetCellData(index / 4);

		dragAreaStartPos = cellData.cellPosition[0] + tilemap1->GetPosition();
		dragAreaRect.setSize({ 16, 16 });
		dragAreaRect.setPosition(dragAreaStartPos);

		cellDatas.push_back(tilemap1->GetCellData(index / 4));
	}
	else if (InputMgr::GetMouseButtonDown(sf::Mouse::Left)) {
		index = -1;
		prevX = -1;
		prevY = -1;
		dragAreaRect.setSize({ 0, 0 });
	}

}

void MapToolScene::DrawColliderBox()
{
	if (drawCollider) {
		if (InputMgr::GetMouseButtonDown(sf::Mouse::Left)) {
			startDraw = true;
			colliders.push_back(new sf::RectangleShape());
			colliders[colliders.size() - 1]->setFillColor(sf::Color::Transparent);
			colliders[colliders.size() - 1]->setOutlineColor(sf::Color::Red);
			colliders[colliders.size() - 1]->setOutlineThickness(1.f);
			drawStartPos = ScreenToWorld(InputMgr::GetMousePosition());
			colliders[colliders.size() - 1]->setPosition(drawStartPos);
		}
		else if (InputMgr::GetMouseButton(sf::Mouse::Left) && startDraw) {
			sf::RectangleShape& col = *colliders[colliders.size() - 1];
			sf::Vector2f mousePosition = ScreenToWorld(InputMgr::GetMousePosition());
			col.setSize(mousePosition - drawStartPos);
		}
		else if (InputMgr::GetKey(sf::Keyboard::LControl) && InputMgr::GetKeyDown(sf::Keyboard::Z)) {
			if (colliders.size() > 0) {
				delete colliders[colliders.size() - 1];
				colliders.resize(colliders.size() - 1);
			}
		}
		else if (InputMgr::GetMouseButtonUp(sf::Mouse::Left) && startDraw) {
			startDraw = false;
			if (colliders[colliders.size() - 1]->getSize().x == 0 || colliders[colliders.size() - 1]->getSize().y == 0) {
				delete colliders[colliders.size() - 1];
				colliders.resize(colliders.size() - 1);
			}
		}
	}
}

void MapToolScene::DrawTriggerBox()
{
	if (drawTrigger) {
		if (InputMgr::GetMouseButtonDown(sf::Mouse::Left)) {
			startDraw = true;
			drawStartPos = ScreenToWorld(InputMgr::GetMousePosition());
			triggers.push_back(new Trigger());
			triggers[triggers.size() - 1]->Init();
			triggers[triggers.size() - 1]->SetPosition(drawStartPos);
		}
		else if (InputMgr::GetMouseButton(sf::Mouse::Left) && startDraw) {
			Trigger& tri = *triggers[triggers.size() - 1];
			sf::Vector2f mousePosition = ScreenToWorld(InputMgr::GetMousePosition());
			tri.SetSize(mousePosition - drawStartPos);
		}
		else if (InputMgr::GetKey(sf::Keyboard::LControl) && InputMgr::GetKeyDown(sf::Keyboard::Z) && drawTrigger) {
			if (triggers.size() > 0) {
				delete triggers[triggers.size() - 1];
				triggers.resize(triggers.size() - 1);
			}
		}
		else if (InputMgr::GetMouseButtonUp(sf::Mouse::Left) && startDraw) {
			startDraw = false;
			isShowTriggerBox = true;
			if (triggers[triggers.size() - 1]->GetSize().x == 0 || triggers[triggers.size() - 1]->GetSize().y == 0) {
				delete triggers[triggers.size() - 1];
				triggers.resize(triggers.size() - 1);
			}
		}
	}
}
