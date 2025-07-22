#include "stdafx.h"
#include "SceneGame.h"
#include "TileMap.h"
#include "SpriteGo.h"
SceneGame::SceneGame() 
	: Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	SpriteGo* sp = new SpriteGo("assets100V20104.png");

	AddGameObject(sp);
	Scene::Init();
}

void SceneGame::Enter()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(false);

	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	worldView.setSize(windowSize);
	worldView.setCenter({0.f, 0.f});

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);

	Scene::Enter();

}

void SceneGame::Exit()
{

	
	Scene::Exit();
}

void SceneGame::Update(float dt)
{

	Scene::Update(dt);

	
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);

	window.setView(uiView);
	window.draw(cursor);
}

void SceneGame::SpawnZombies(int count)
{
}
