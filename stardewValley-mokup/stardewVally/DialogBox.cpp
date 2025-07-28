#include "stdafx.h"
#include "DialogBox.h"
DialogBox::DialogBox(const std::string& name)
	: GameObject(name)
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 2;
}

void DialogBox::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	boxSprite.setPosition(pos);
}

void DialogBox::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	boxSprite.setRotation(rot);
}

void DialogBox::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	boxSprite.setScale(s);
}

void DialogBox::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	boxSprite.setOrigin(o);
}

void DialogBox::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(boxSprite, preset);
	}
}

void DialogBox::Init()
{
}

void DialogBox::Release()
{
}

void DialogBox::Reset()
{
}

void DialogBox::Update(float dt)
{
}

void DialogBox::Draw(sf::RenderWindow& window)
{
}