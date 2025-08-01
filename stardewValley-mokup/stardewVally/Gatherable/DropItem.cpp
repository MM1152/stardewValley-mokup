#include "stdafx.h"
#include "DropItem.h"
#include "Inventory.h"
#include "Player.h"
#include "SceneTest.h"
DropItem::DropItem(const std::string& name,const std::string& Id)
	: GameObject(name)
	,dropitemId(Id)
{
}

void DropItem::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;

}

void DropItem::Release()
{
}

void DropItem::Reset()
{
	dropitem.setTexture(TEXTURE_MGR.Get(dropitemId));
}

void DropItem::Update(float dt)
{
	Map* map = player->GetMap();

	sf::Vector2i lookDir = player->GetLookDir();
	sf::Vector2f holePos = { player->GetPosition().x + (lookDir.x * 16.f) , player->GetPosition().y + (lookDir.y * 16.f) };
	int cellIdx = map->GetCellIndex(holePos, 0);
	CellData& cellData = map->GetCell(cellIdx, 0);

	SceneTest* scene = (SceneTest*)SCENE_MGR.GetCurrentScene();
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Right) || InputMgr::GetKeyDown(sf::Keyboard::C))
	{
		if(cellData.cellPosition[0] == GetPosition())
		{ 
			if (dropitemId == "graphics/parsnipdrop.png")
			{
				ItemInfo info = itemDataMgr::Instance().GetItem("parsnip");
		
				inventory->AddItem(info);
				cellData.ge = GatherableType::None;
				scene->RemoveDropItem(this);
			}
			if (dropitemId == "graphics/garlicdrop.png")
			{
				ItemInfo info = itemDataMgr::Instance().GetItem("garlic");
				inventory->AddItem(info);
				cellData.ge = GatherableType::None;
				scene->RemoveDropItem(this);
			}
			if (dropitemId == "graphics/cauliflowerdrop.png")
			{
				ItemInfo info = itemDataMgr::Instance().GetItem("cauliflower");
				inventory->AddItem(info);
				cellData.ge = GatherableType::None;
				scene->RemoveDropItem(this);
			}
			if (dropitemId == "graphics/potatodrop.png")
			{
				ItemInfo info = itemDataMgr::Instance().GetItem("potato");
				inventory->AddItem(info);
				cellData.ge = GatherableType::None;
				scene->RemoveDropItem(this);
			}
		}
	}
	inventory->Update(dt);
}

void DropItem::Draw(sf::RenderWindow& window)
{
	window.draw(dropitem);
}


void DropItem::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	dropitem.setPosition(pos);
}

void DropItem::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	dropitem.setRotation(rot);
}

void DropItem::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	dropitem.setScale(s);
}

void DropItem::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	dropitem.setOrigin(o);
}

void DropItem::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(dropitem, preset);
	}
}

