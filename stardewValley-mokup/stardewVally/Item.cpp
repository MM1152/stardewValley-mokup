#include "stdafx.h"
#include "Item.h"

Item::Item(const std::string& texId, const std::string& name)
	:GameObject(texId)
	,texId(texId)
{
}

void Item::Init()
{
	testItemImage.setFillColor(sf::Color::Red);
	testItemImage.setRadius(15);
}

void Item::Release()
{
}

void Item::Reset()
{
	Utils::SetOrigin(testItemImage , Origins::MC);
}

void Item::Update(float dt)
{
	if (isDrag) {
		 SetPosition((sf::Vector2f)InputMgr::GetMouseUIRect().getPosition());
	}
}

void Item::Draw(sf::RenderWindow& window)
{
	window.draw(testItemImage);
}

void Item::SetRotation(float rot)
{
	rotation = rot;
	testItemImage.setRotation(rot);
}

void Item::SetScale(const sf::Vector2f& s)
{
	scale = s;
	testItemImage.setScale(s);
}

void Item::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	testItemImage.setPosition(pos);
}

void Item::DragItem()
{
	isDrag = true;
}
