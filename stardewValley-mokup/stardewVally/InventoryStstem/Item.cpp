#include "stdafx.h"
#include "Item.h"

Item::Item(ItemInfo type)	
	:GameObject(type.itemName)
	,iteminfo(type)
{
}

void Item::Init()
{

}

void Item::Release()
{
}

void Item::Reset()
{
	itemSp.setTexture(TEXTURE_MGR.Get(iteminfo.itemTextureId));
	Utils::SetOrigin(itemSp , Origins::MC);
}

void Item::Update(float dt)
{
	if (isDrag) {
		 SetPosition((sf::Vector2f)InputMgr::GetMouseUIRect().getPosition());
	}
}

void Item::Draw(sf::RenderWindow& window)
{
	window.draw(itemSp);
}

void Item::SetRotation(float rot)
{
	rotation = rot;
	itemSp.setRotation(rot);
}

void Item::SetScale(const sf::Vector2f& s)
{
	scale = s;
	itemSp.setScale(s);
}

void Item::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	itemSp.setPosition(pos);
}

void Item::SetItemInfo(Item* item)
{
	iteminfo = item->iteminfo;
	
	itemSp.setTexture(TEXTURE_MGR.Get(iteminfo.itemTextureId) , true);
}

void Item::DragItem()
{
	isDrag = true;
}
