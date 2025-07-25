#include "stdafx.h"
#include "SceneHome.h"
#include "TileMap.h"
#include "SpriteGo.h"
#include "Player.h"
#include "NpcMgr.h"
#include "Shop.h"
#include "Collider.h"
#include "TimeMoneyUi.h"

SceneHome::SceneHome()
	: Scene(SceneIds::Home)
{
}

void SceneHome::Init()
{
	texIds.push_back("graphics/myhome.bmp");
	

	Scene::Init();
	home.setTexture(TEXTURE_MGR.Get("graphics/myhome.bmp"));
}

void SceneHome::Enter()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(true);
	worldView.setSize({ FRAMEWORK.GetWindowSizeF().x, FRAMEWORK.GetWindowSizeF().y });

	uiView.setSize(FRAMEWORK.GetWindowSizeF());
	uiView.setCenter({ FRAMEWORK.GetWindowSizeF().x / 2 , FRAMEWORK.GetWindowSizeF().y / 2 });
	Scene::Enter();
}

void SceneHome::Update(float dt)
{
	Scene::Update(dt);
}

void SceneHome::Draw(sf::RenderWindow& window)
{

	Scene::Draw(window);
	window.draw(home);
}
