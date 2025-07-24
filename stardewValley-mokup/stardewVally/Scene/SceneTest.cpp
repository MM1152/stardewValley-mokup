#include "stdafx.h"
#include "SceneTest.h"
#include "TimeMoneyUi.h"

SceneTest::SceneTest()
	: Scene(SceneIds::Test)
{
}

void SceneTest::Init()
{
	worldView.setSize(FRAMEWORK.GetWindowSizeF());
	worldView.setCenter({ FRAMEWORK.GetWindowSizeF().x / 2 , FRAMEWORK.GetWindowSizeF().y / 2 });
	uiView.setSize(FRAMEWORK.GetWindowSizeF());
	uiView.setCenter({ FRAMEWORK.GetWindowSizeF().x / 2 , FRAMEWORK.GetWindowSizeF().y / 2 });

	texIds.push_back("graphics/½Ã°è.png");
	texIds.push_back("graphics/µ· ¼ýÀÚ.png");
	texIds.push_back("graphics/³¯¾¾.bmp");
	texIds.push_back("graphics/°èÀý.bmp");

	fontIds.push_back("fonts/SDMisaeng.ttf");
	fontIds.push_back("fonts/DOSGothic.ttf");
	fontIds.push_back("fonts/DungGeunMo.ttf");

	timemoney = (TimeMoneyUi*)AddGameObject(new TimeMoneyUi());

	Scene::Init();
}

void SceneTest::Enter()
{
	Scene::Enter();
}

void SceneTest::Update(float dt)
{
	Scene::Update(dt);
}