#include "stdafx.h"
#include "SceneDev1.h"
#include "TextGo.h"
#include "Framework.h"
#include "ResourceMgr.h"
#include "InputMgr.h"
#include "SceneMgr.h"
#include "Inventory.h"
SceneDev1::SceneDev1() : Scene(SceneIds::Dev1)
{
}

SceneDev1::~SceneDev1()
{

}

void SceneDev1::Init()
{
	inven = new Inventory();

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
