#include "stdafx.h"
#include "SceneDev1.h"
#include "TextGo.h"
#include "Framework.h"
#include "ResourceMgr.h"
#include "InputMgr.h"
#include "SceneMgr.h"
#include "Inventory.h"
#include "QuickBar.h"
SceneDev1::SceneDev1() : Scene(SceneIds::Dev1)
{	
}

SceneDev1::~SceneDev1()
{

}

void SceneDev1::Init()
{
	texIds.push_back(INVEN_IMG_PATH"ItemSlot.png");
	texIds.push_back(ITEM_IMG_PATH"galaxy_sword.png");
	texIds.push_back(INVEN_IMG_PATH"CraftImage.bmp");

	inven = new Inventory(INVEN_IMG_PATH"CraftImage.bmp");
	quickBar = new QuickBar(INVEN_IMG_PATH"CraftImage.bmp");

	inven->SetQuickBar(quickBar);

	AddGameObject(quickBar);
	AddGameObject(inven);
	Scene::Init();
}

void SceneDev1::Update(float dt)
{
	Scene::Update(dt);
	if (InputMgr::GetKeyDown(sf::Keyboard::E)) {
		inven->SetActive(!inven->GetActive());
	}

	
}

void SceneDev1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);

	window.draw(InputMgr::rect);
}
