#include "stdafx.h"
#include "TestScene.h"

TestScene::TestScene()
	:Scene(SceneIds::TestScene)
{
}

void TestScene::Init()
{
	shape.setFillColor(sf::Color::Red);
	shape.setRadius(50);
}

void TestScene::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	window.draw(shape);
}
