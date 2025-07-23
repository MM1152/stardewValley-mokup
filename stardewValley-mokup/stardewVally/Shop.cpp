#include "stdafx.h"
#include "Shop.h"

Shop::Shop(const std::string& name)
	: GameObject(name)
{
}

void Shop::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	sprite.setPosition(pos);
}

void Shop::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	sprite.setRotation(rot);
}

void Shop::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	sprite.setScale(s);
}

void Shop::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	sprite.setOrigin(o);
}

void Shop::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(sprite, preset);
	}
}

void Shop::Init()
{
}

void Shop::Release()
{
}

void Shop::Reset()
{
}

void Shop::Update(float dt)
{
}

void Shop::Draw(sf::RenderWindow& window)
{
	if (isUiShow == true)
	{
		window.draw(sprite);
	}
}

void Shop::ShowUi()
{
	isUiShow = true;
	SetPosition({ -500.f, 0.f });

	sprite.setTexture(TEXTURE_MGR.Get("graphics/uitest.png"));
}

void Shop::CloseUi()
{
	isUiShow = false;
}

bool Shop::isUiShowing()
{
	return isUiShow;
}
