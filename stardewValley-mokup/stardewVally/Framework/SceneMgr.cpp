#include "stdafx.h"
#include "SceneMgr.h"
#include "SceneDev1.h"
#include "SceneTest.h"
#include "SceneGame.h"
#include "SceneAnimator.h"
#include "MapToolScene.h"
#include "LoadMapDataScene.h"
#include "SceneTileChangeTest.h"
#include "SceneHome.h"
#include "SceneAnimationTest.h"
void SceneMgr::Init()
{
	scenes.insert({ SceneIds::Dev1, new SceneDev1() });
	scenes.insert({ SceneIds::Animator, new SceneAnimator() });
	scenes.insert({ SceneIds::Maptool, new MapToolScene() });
	scenes.insert({ SceneIds::LoadMapTest, new LoadMapDataScene() });
	scenes.insert({ SceneIds::Test, new SceneTest() });
	scenes.insert({ SceneIds::Game, new SceneGame() });
	scenes.insert({ SceneIds::Animator, new SceneAnimator() });
	scenes.insert({ SceneIds::ChangeTile, new SceneTileChangeTest() });
	scenes.insert({ SceneIds::Home, new SceneHome() });
	scenes.insert({ SceneIds::AnimationTest , new SceneAnimationTest() });
	
	for (auto scene : scenes)
	{
		scene.second->Init();
	}

	currentScene = startScene;
	scenes[currentScene]->Enter();
}

void SceneMgr::Release()
{
	for (auto scene : scenes)
	{
		if (scene.second->Id == currentScene)
		{
			scene.second->Exit();
		}
		scene.second->Release();
		delete scene.second;
	}
	scenes.clear();
}

void SceneMgr::ChangeScene(SceneIds id)
{
	nextScene = id;
}

void SceneMgr::Update(float dt)
{
	if (nextScene != SceneIds::None)
	{
		scenes[currentScene]->Exit();
		currentScene = nextScene;
		nextScene = SceneIds::None;
		scenes[currentScene]->Enter();
	}

	scenes[currentScene]->Update(dt);
}

void SceneMgr::Draw(sf::RenderWindow& window)
{
	scenes[currentScene]->Draw(window);
}
