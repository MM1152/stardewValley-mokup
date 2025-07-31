#include "stdafx.h"
#include "SceneTest.h"
#include "TileMap.h"
#include "SpriteGo.h"
#include "Player.h"
#include "NpcMgr.h"
#include "Shop.h"
#include "Collider.h"
#include "TimeMoneyUi.h"
#include "Inventory.h"
#include "QuickBar.h"
#include "DialogueBox.h"
#include "DialogueLoader.h"
#include "Crops.h"
#include "InteractionObject.h"
#include "DropItem.h"
#include "SellBox.h"
#include "Scene.h"

Player* Scene::player;
TimeMoneyUi* Scene::timemoney;
Inventory* Scene::inventory;
QuickBar* Scene::quickBar;

bool Scene::releasePlayer;
bool Scene::releaseTimeMoney;
bool Scene::releaseInven;
bool Scene::releaseQuick;

Scene::Scene(SceneIds id)
	: Id(id)
{
}

void Scene::Init()
{
	if (!player) {
		inventory = new Inventory(INVEN_IMG_PATH"CraftImage.bmp" , "Inven");
		quickBar = new QuickBar(INVEN_IMG_PATH"CraftImage.bmp", "fonts/DOSGothic.ttf" , "QuickBar");
		player = new Player("Player");
		timemoney = new TimeMoneyUi("TimeMoney");
	}

	for (auto obj : gameObjects)
	{
		obj->Init();
	}

	for (auto obj : objectsToAdd)
	{
		obj->Init();
	}
}

void Scene::Release()
{
	ApplyPendingChanges();
	
	for (auto obj : gameObjects)
	{
		if (obj == player && releasePlayer) continue;
		if (obj == inventory && releaseInven) continue;
		if (obj == quickBar && releaseQuick) continue;
		if (obj == timemoney && releaseTimeMoney) continue;

		if (obj) {
			obj->Release();
		}
		if (obj) {
			delete obj;
		}

		if (obj == player) releasePlayer = true;
		if (obj == inventory) releaseInven = true;
		if (obj == quickBar) releaseQuick = true;
		if (obj == timemoney) releaseTimeMoney = true;

	}
	gameObjects.clear();
}

void Scene::Enter()
{
	TEXTURE_MGR.Load(texIds);
	FONT_MGR.Load(fontIds);
	SOUNDBUFFER_MGR.Load(soundIds);
	ANI_CLIP_MGR.Load(aniIds);

	for (auto obj : gameObjects)
	{
		obj->Reset();
	}

	for (auto obj : objectsToAdd)
	{
		obj->Reset();
	}
}

void Scene::Exit()
{
	ApplyPendingChanges();
	
	TEXTURE_MGR.Unload(texIds);
	FONT_MGR.Unload(fontIds);
	SOUNDBUFFER_MGR.Unload(soundIds);
	ANI_CLIP_MGR.Load(aniIds);
}

void Scene::Update(float dt)
{
	for (auto obj : gameObjects)
	{
		if (obj->GetActive())
		{
			obj->Update(dt);
		}
	}
}



void Scene::Draw(sf::RenderWindow& window)
{
	std::list<GameObject*> sortedObjects(gameObjects);
	sortedObjects.sort(DrawOrderComparer());

	window.setView(worldView);
	bool isUiView = false;

	for (auto obj : sortedObjects)
	{
		if (obj->sortingLayer >= SortingLayers::UI && !isUiView)
		{
			window.setView(uiView);
			isUiView = true;
		}

		if (obj->GetActive())
		{
			obj->Draw(window);
		}
	}
	ApplyPendingChanges();
}

void Scene::ApplyPendingChanges()
{
	for (GameObject* go : objectsToAdd)
	{
		if (std::find(gameObjects.begin(), gameObjects.end(), go) == gameObjects.end())
		{
			gameObjects.push_back(go);
		}
	}
	objectsToAdd.clear();

	for (GameObject* go : objectsToRemove)
	{
		gameObjects.remove(go);
		if (go != nullptr)
		{
			go->Release();
			delete go;
		}
	}
	objectsToRemove.clear();
}

GameObject* Scene::AddGameObject(GameObject* go)
{
	objectsToAdd.push_back(go);
	return go;
}

void Scene::RemoveGameObject(GameObject* go)
{
	go->SetActive(false);
	objectsToRemove.push_back(go);
}

GameObject* Scene::FindGameObject(const std::string& name)
{
	for (auto obj : gameObjects)
	{
		if (obj->GetName() == name)
		{
			return obj;
		}
	}
	
	for (auto obj : objectsToAdd)
	{
		if (obj->GetName() == name)
		{
			return obj;
		}
	}
	
	return nullptr;
}

std::vector<GameObject*> Scene::FindGameObjects(const std::string& name)
{
	std::vector<GameObject*> results;
	
	for (auto obj : gameObjects)
	{
		if (obj->GetName() == name)
		{
			results.push_back(obj);
		}
	}
	
	for (auto obj : objectsToAdd)
	{
		if (obj->GetName() == name)
		{
			results.push_back(obj);
		}
	}
	
	return results;
}

void Scene::FindGameObjects(const std::string& name, std::vector<GameObject*>& results)
{
	for (auto obj : gameObjects)
	{
		if (obj->GetName() == name)
		{
			results.push_back(obj);
		}
	}
	
	for (auto obj : objectsToAdd)
	{
		if (obj->GetName() == name)
		{
			results.push_back(obj);
		}
	}
}

sf::Vector2f Scene::ScreenToWorld(sf::Vector2i screenPos)
{
	return FRAMEWORK.GetWindow().mapPixelToCoords(screenPos, worldView);
}

sf::Vector2i Scene::WorldToScreen(sf::Vector2f worldPos)
{
	return FRAMEWORK.GetWindow().mapCoordsToPixel(worldPos, worldView);
}

sf::Vector2f Scene::ScreenToUi(sf::Vector2i screenPos)
{
	return FRAMEWORK.GetWindow().mapPixelToCoords(screenPos, uiView);
}

sf::Vector2i Scene::UiToScreen(sf::Vector2f uiPos)
{
	return FRAMEWORK.GetWindow().mapCoordsToPixel(uiPos, uiView);
}
