#include "stdafx.h"
#include "Crops.h"
#include "Map.h"
#include "Player.h"

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

void Crops::GrowUp(int grow)
{
	sf::IntRect Grow(16 * grow, 0, 16, 16);
	crops.setTextureRect(Grow);
	if (grow > 5)
	{
		grow = 5;
		sf::IntRect Grow(16 * grow, 0, 16, 16);
		crops.setTextureRect(Grow);
	}
}

void Crops::SetCropsType(CropsType c)
{
	ctype = c;
	switch (ctype)
	{
	case CropsType::Parsnip:
		cropsId = "crops/parsnip.png";
		sf::IntRect seed(0, 0, 16, 16);
		//crops.setTextureRect(seed);
	}

	

}
