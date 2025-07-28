#include "stdafx.h"
#include "Item.h"

Item::Item(ItemInfo type , bool isUi)
	:GameObject(type.itemName)
	,iteminfo(type)
	,isUi(isUi)
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
	
	if (isUi) {
		itemSp.setScale({ 2.f,2.f });
	}
	else {
		itemSp.setScale({ 1.f,1.f });
	}

	if (iteminfo.textureCoord.width == -1 && iteminfo.textureCoord.height == -1) {
		itemSp.setTexture(TEXTURE_MGR.Get(iteminfo.itemTextureId), true);
	}
	else if (iteminfo.uiTextCoord.width == -1 && iteminfo.uiTextCoord.height == -1)
	{
		itemSp.setTexture(TEXTURE_MGR.Get(iteminfo.itemTextureId), true);
	}
	else {
		if (isUi) {
			itemSp.setTexture(TEXTURE_MGR.Get(iteminfo.itemTextureId));
			itemSp.setTextureRect((sf::IntRect)iteminfo.uiTextCoord);
		}
		else {
			itemSp.setTexture(TEXTURE_MGR.Get(iteminfo.itemTextureId));
			itemSp.setTextureRect((sf::IntRect)iteminfo.textureCoord);
		}

	}
	Utils::SetOrigin(itemSp , Origins::MC);
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
	Reset();
}


