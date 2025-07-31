#include "stdafx.h"
#include "SceneTitle.h"

SceneTitle::SceneTitle()
	: Scene(SceneIds::Title)
{
}

void SceneTitle::Init()
{
	texIds.push_back("title/main.bmp");
	texIds.push_back("title/mainchoice.png");
	texIds.push_back("title/yes_or_no.png");
	texIds.push_back("title/yes.png");
	texIds.push_back("title/no.png");
	texIds.push_back("title/choicetool.png");
	texIds.push_back("title/maptool.png");
	texIds.push_back("title/animator.png");


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