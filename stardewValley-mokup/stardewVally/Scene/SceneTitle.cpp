#include "stdafx.h"
#include "SceneTitle.h"

SceneTitle::SceneTitle()
	: Scene(SceneIds::Title)
{
}

void SceneTitle::Init()
{
	texIds.push_back("graphics/main.bmp");
	texIds.push_back("graphics/mainchoice.png");
	texIds.push_back("graphics/yes_or_no.png");
	texIds.push_back("graphics/yes.png");
	texIds.push_back("graphics/no.png");


	fontIds.push_back("fonts/Stardew_Valley.ttf");

	titleui = new TitleUi;
	AddGameObject(titleui);

	
	Scene::Init();
}

void SceneTitle::Enter()
{
	worldView.setSize({ FRAMEWORK.GetWindowSizeF()});
	worldView.setCenter({ titleui->GetPosition().x / 2 , titleui->GetPosition().y / 2 });

	uiView.setSize(FRAMEWORK.GetWindowSizeF());
	uiView.setCenter({ FRAMEWORK.GetWindowSizeF().x / 2 , FRAMEWORK.GetWindowSizeF().y / 2 });

	Scene::Enter();
}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);
}