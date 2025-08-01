#include "stdafx.h"
#include "InteractionObject.h"
#include "Map.h"
InteractionObject::InteractionObject(const std::string& texId, CellData* cellData, const std::string& name)
	:GameObject(name)
	,cellData(cellData)
	,texId(texId)
{
}

void InteractionObject::SetRotation(float rot)
{
	rotation = rot;
	objectSp.setRotation(rot);
}

void InteractionObject::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	objectSp.setPosition(pos);
}

void InteractionObject::SetScale(const sf::Vector2f& s)
{
	scale = s;
	objectSp.setScale(s);
}

void InteractionObject::SetOrigin(Origins preset)
{
	originPreset = preset;
	Utils::SetOrigin(objectSp, preset);
}

void InteractionObject::SetOrigin(const sf::Vector2f& o)
{
	origin = o;
	originPreset = Origins::Custom;
	objectSp.setOrigin(o);
}

void InteractionObject::Init()
{
}

void InteractionObject::Release()
{
}

void InteractionObject::Reset()
{
	TEXTURE_MGR.Load(texId);

	int left = cellData->cellTextCoord[0].x;
	int top = cellData->cellTextCoord[0].y;
	int width = 16;
	int height = 16;

	sf::IntRect rect = {left , top , width , height};
	objectSp.setTexture(TEXTURE_MGR.Get(texId));
	objectSp.setTextureRect(rect);

	objectSp.setPosition(cellData->cellPosition[0]);

	this->rect.setSize({16 , 16});
	this->rect.setPosition(objectSp.getPosition());

	sortingLayer = SortingLayers::Foreground;
	sortingOrder = objectSp.getPosition().y;
}

void InteractionObject::Update(float dt)
{
}

void InteractionObject::Draw(sf::RenderWindow& window)
{
	window.draw(objectSp);
}

void InteractionObject::Interaction()
{
	SetActive(false);
	rect.setSize({ 0,0 });
}
