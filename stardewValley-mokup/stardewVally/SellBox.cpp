#include "stdafx.h"
#include "SellBox.h"
#include "Inventory.h"
#include "Player.h"

SellBox::SellBox(const std::string& name)
	: GameObject(name)
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
}

void SellBox::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	sellBoxSprite.setPosition(pos);
	boxRect.setPosition(pos);
}

void SellBox::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	sellBoxSprite.setRotation(rot);
}

void SellBox::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	sellBoxSprite.setScale(s);
}

void SellBox::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	sellBoxSprite.setOrigin(o);
	boxRect.setOrigin(o);
}

void SellBox::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(sellBoxSprite, preset);
		Utils::SetOrigin(boxRect,preset);
	}
}

void SellBox::Init()
{
}

void SellBox::Release()
{
}

void SellBox::Reset()
{
	sellBoxSprite.setTexture(TEXTURE_MGR.Get("graphics/sellbox.png"));
	sellBoxSprite.setScale(1.f, 1.f);
	sellBoxSprite.setPosition({ 280.f,190.f });

	sf::FloatRect currentBounds = sellBoxSprite.getGlobalBounds();
	boxRect.setSize({ currentBounds.width + 10, currentBounds.height + 10});
	boxRect.setPosition(sellBoxSprite.getPosition().x-5, sellBoxSprite.getPosition().y);
	boxRect.setFillColor(sf::Color(0, 0, 255, 150));
}

void SellBox::Update(float dt)
{

	playerRect.setPosition(player->GetPosition()); 
	playerRect.setSize(player->GetGlobalBounds().getSize());

	player->SetPosition(playerRect.getPosition());

	if (IsCollidingBox(playerRect))
	{
		if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
		{
			bool active = !inventory->GetActive();
			inventory->SetActive(active);

			if (active)
			{
				sf::Vector2f invPos = inventory->GetPosition();
				inventory->SetPosition({ invPos.x, invPos.y + 200.f });
			}
		}
		else if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
		{
			inventory->SetActive(!active);
		}
	}
}

void SellBox::Draw(sf::RenderWindow& window)
{
	window.draw(sellBoxSprite);
}

//void SellBox::setCallBack(std::function<void()> cb)
//{
//	callback = cb;
//}

bool SellBox::IsCollidingBox(sf::RectangleShape rect)
{
	sf::Vector2f boxPos = boxRect.getPosition();
	sf::Vector2f boxSize = boxRect.getGlobalBounds().getSize();

	sf::Vector2f rectPos = rect.getPosition();
	sf::Vector2f rectSize = rect.getGlobalBounds().getSize();

	return boxPos.x < rectPos.x + rectSize.x &&
		rectPos.x < boxPos.x + boxSize.x &&
		boxPos.y < rectPos.y + rectSize.y &&
		rectPos.y < boxPos.y + boxSize.y;
}

void SellBox::SetInventory(Inventory* inven)
{
	inventory = inven;
}

Inventory* SellBox::GetInventory()
{
	return inventory;
}

void SellBox::SetPlayer(Player* p)
{
	player = p;
}

Player* SellBox::GetPlayer()
{
	return player;
}

