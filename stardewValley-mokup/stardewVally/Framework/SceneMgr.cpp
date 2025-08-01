#include "stdafx.h"
#include "SceneMgr.h"
#include "SceneFarm.h"
#include "SceneAnimator.h"
#include "MapToolScene.h"
#include "SceneHome.h"
#include "SceneTitle.h"
#include "SceneVillige.h"
#include "SceneStore.h"

void SceneMgr::Init()
{
	scenes.insert({ SceneIds::Animator, new SceneAnimator() });
	scenes.insert({ SceneIds::Maptool, new MapToolScene() });
	scenes.insert({ SceneIds::Title, new SceneTitle() });

	scenes.insert({ SceneIds::Home, new SceneHome() });
	scenes.insert({ SceneIds::Farm, new SceneFarm() });
	scenes.insert({ SceneIds::Village, new SceneVillige() });
	scenes.insert({ SceneIds::Store, new SceneStore() });

	
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
