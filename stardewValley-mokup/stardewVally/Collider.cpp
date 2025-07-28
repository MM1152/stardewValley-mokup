#include "stdafx.h"
#include "Collider.h"
#include "Map.h"

Collider::Collider(const std::string& name)
	: GameObject(name)
{
}

void Collider::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	shape.setPosition(pos);
}

void Collider::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	shape.setRotation(rot);
}

void Collider::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	shape.setScale(s);
}

void Collider::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	shape.setOrigin(o);
}

void Collider::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(shape, preset);
	}
}

void Collider::Init()
{
}

void Collider::Release()
{
}

void Collider::Reset()
{ 
}

void Collider::Update(float dt)
{
}

void Collider::Draw(sf::RenderWindow& window)
{
}

bool Collider::IsColliding(const GameObject& sprite)
{
	sf::Vector2f characterPos = sprite.GetPosition();
	sf::Vector2f characterSize = sprite.GetGlobalBounds().getSize();

	for (const auto& shape : shapes)
	{

		if (sprite.GetGlobalBounds().intersects(shape->getGlobalBounds())) {
			return true;
		}

	}
	return false;
}

bool Collider::IsColliding(const sf::Sprite& sprite)
{
	sf::Vector2f characterPos = sprite.getPosition();
	sf::Vector2f characterSize = sprite.getGlobalBounds().getSize();

	for (const auto& shape : shapes)
	{
		sf::Vector2f rectPos = shape->getPosition();
		sf::Vector2f rectSize = shape->getGlobalBounds().getSize();

		if (sprite.getGlobalBounds().intersects(shape->getGlobalBounds())) {
			return true;
		}

	}
	return false;
}

bool Collider::IsColliding(const sf::FloatRect rect)
{
	sf::Vector2f characterPos = rect.getPosition();
	sf::Vector2f characterSize = rect.getSize();

	for (const auto& shape : shapes)
	{
		sf::Vector2f rectPos = shape->getPosition();
		sf::Vector2f rectSize = shape->getGlobalBounds().getSize();

		if (characterPos.x < rectPos.x + rectSize.x &&
			rectPos.x < characterPos.x + characterSize.x &&
			characterPos.y < rectPos.y + rectSize.y &&
			rectPos.y < characterPos.y + characterSize.y)
		{
			return true;
		}
	}
	return false;
}

void Collider::areaBlocked(sf::Vector2f& position, GameObject& sprite, const sf::Vector2f& moveOffset)
{
	position.x += moveOffset.x;
	sprite.SetPosition(position);
	for (auto shape : shapes)
	{
		if (IsColliding(sprite))
		{
			position.x -= moveOffset.x;
			sprite.SetPosition(position);
		}
	}

	position.y += moveOffset.y;
	sprite.SetPosition(position);
	for (auto shape : shapes)
	{
		if (IsColliding(sprite))
		{
			position.y -= moveOffset.y;
			sprite.SetPosition(position);
		}
	}
}

void Collider::areaBlocked(sf::Vector2f& position, sf::Sprite& sprite, const sf::Vector2f& moveOffset)
{
	position.x += moveOffset.x;
	sprite.setPosition(position);
	for (auto shape : shapes)
	{
		if (IsColliding(sprite))
		{
			position.x -= moveOffset.x;
			sprite.setPosition(position);
		}
	}

	position.y += moveOffset.y;
	sprite.setPosition(position);
	for (auto shape : shapes)
	{
		if (IsColliding(sprite))
		{
			position.y -= moveOffset.y;
			sprite.setPosition(position);
		}
	}
}

void Collider::SetMap(Map* map)
{
	this->map = map;

	for (sf::RectangleShape* col: map->GetColliders())
	{
		shapes.push_back(col);
	}
}


