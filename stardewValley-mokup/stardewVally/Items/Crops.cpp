#include "stdafx.h"
#include "Crops.h"
#include "TimeMoneyUi.h"

Crops::Crops(const std::string& name)
	: GameObject(name)
{
}
void Crops::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	crops.setPosition(pos);
}
void Crops::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	crops.setRotation(rot);
}
void Crops::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	crops.setScale(s);
}
void Crops::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	crops.setOrigin(o);
}
void Crops::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(crops, preset);
	}
}
void Crops::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;


	SetCropsType(ctype);
	SetScale({ 1.f, 1.f });
}
void Crops::Release()
{
}
void Crops::Reset()
{
	crops.setTexture(TEXTURE_MGR.Get(cropsId));
}
void Crops::Update(float dt)
{
}
void Crops::Draw(sf::RenderWindow& window)
{
	window.draw(crops);
}

void Crops::GrowUp(){
	curGrow++;
	sf::IntRect Grow(16 * curGrow, 0, 16, 16);
	crops.setTextureRect(Grow);
	if (curGrow > 5)
	{
		curGrow = 5;
		sf::IntRect Grow(16 * curGrow, 0, 16, 16);
		crops.setTextureRect(Grow);
	}
}

void Crops::Setidx(int index)
{
	idx = index;
}

int Crops::Getidx()
{
	return idx;
}

void Crops::SetCropsType(CropsType c)
{
	ctype = c;
	switch (ctype)
	{
	case CropsType::Parsnip:
		cropsId = "graphics/parsnip.png";
		sf::IntRect seed(0, 0, 16, 16);
		crops.setTextureRect(seed);
		break;
	}
}

Crops::CropsType Crops::GetCropsType()
{
	return ctype;
}

void Crops::SetTimeMoneyUi(TimeMoneyUi* time)
{
	tm = time;
}

TimeMoneyUi* Crops::GetTimeMoneyUi()
{
	return tm;
}
