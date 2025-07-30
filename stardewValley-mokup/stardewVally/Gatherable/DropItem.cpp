#include "stdafx.h"
#include "DropItem.h"
#include "Inventory.h"
#include "Player.h"




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

