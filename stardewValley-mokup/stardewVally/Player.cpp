#include "stdafx.h"
#include "Player.h"
#include "NpcMgr.h"
#include "inventory.h"
#include "TimeMoneyUi.h"
#include "TileMap.h"
#include "Map.h"


Player::Player(const std::string name)
	:Collider(name)
{
}

void Player::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	sprite.setPosition(pos);
}

void Player::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	sprite.setRotation(rot);
}

void Player::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	sprite.setScale(s);
}

void Player::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	sprite.setOrigin(o);
}
void Player::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(sprite, preset);
	}
}

void Player::Init()
{
	seedGuideRect.setSize({16.f, 16.f});
	seedGuideRect.setFillColor(sf::Color(0, 255, 0, 128));
	seedGuideRect.setOutlineColor(sf::Color::Green);
	if (inventory)
	{
		inventory->SetActive(false);
	}
	isPlayer = true;
	Collider::Init();
}

void Player::Release()
{
}

void Player::Reset()
{
	sprite.setTexture(TEXTURE_MGR.Get("graphics/testC.png"));
	SetOrigin(Origins::BL);

	speed = 100;
}

void Player::Update(float dt)
{
	sf::Vector2f movement = { 0.f, 0.f };

	float moveX = InputMgr::GetAxisRaw(Axis::Horizontal);
	float moveY = InputMgr::GetAxisRaw(Axis::Vertical);

	movement.x = moveX * speed * dt;
	movement.y = moveY * speed * dt;

	sf::Vector2f moveOffset(movement.x, movement.y);

	if (isPlayer)
	{
		Collider::areaBlocked(position, *this, moveOffset);
	}
	//player 충돌 로직
	/*if (npcMgr != nullptr)
	{
		sf::Vector2f npcPos = npcMgr->GetPosition();
		sf::Vector2f npcSize = npcMgr->GetGlobalBounds().getSize();
		sf::Vector2f playerSize = sprite.getGlobalBounds().getSize();
>>>>>>> 357149e9b2d22b50f698e2af380b636a38f4ec6c

		float nextPlayerX = position.x + moveOffset.x;
		bool colliedX = false;

		if (nextPlayerX < npcPos.x + npcSize.x &&
			npcPos.x < nextPlayerX + playerSize.x &&
			position.y < npcPos.y + npcSize.y &&
			npcPos.y < position.y + playerSize.y)
		{
			if (moveOffset.x >= 0.f )
			{
				position.x = npcPos.x - playerSize.x;
				std::cout << "npc colliding" << std::endl;
			}
			else if (moveOffset.x <= 0.f)
			{
				position.x = npcPos.x + playerSize.x;
			}

			moveOffset.x = 0.f;
			colliedX = true;
		}

		float nextPlayerY = position.y + moveOffset.y;
		bool colliedY = false;

		if (position.x < npcPos.x + npcSize.x &&
			npcPos.x < position.x + playerSize.x &&
			nextPlayerY < npcPos.y + npcSize.y &&
			npcPos.y < nextPlayerY + playerSize.y)
		{
			if (moveOffset.y >= 0.f)
			{
				position.y = npcPos.y - playerSize.y;
			}
			else if (position.y <= 0.f)
			{
				position.y = npcPos.y + playerSize.y;
			}

			moveOffset.y = 0.f;
			colliedY = true;

		}

		if (!colliedX)
		{
			position.x += movement.x;
		}
		if (!colliedY)
		{
			position.y += movement.y;
		}
		sprite.setPosition(position);
	}*/
	// openInventory > E (in / out)

	if (!openShop)
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::E))
		{
			ChangeisPlayer();
			ChangeOpenInven();
			timemoneyui->ChangeTimer();
			inventory->SetActive(!inventory->GetActive());
		}
	}
	// openInven > Escape out
	if (openInven)
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
		{
			ChangeisPlayer();
			ChangeOpenInven();
			timemoneyui->ChangeTimer();
			inventory->SetActive(!inventory->GetActive());
		}
	}

	if (!openShop && !openInven && fainting)
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::Return))
		{
			timemoneyui->Changeth();
			isPlayer = true;
			fainting = false;
		}
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void Player::SetInventory(Inventory* inven)
{
	this->inventory = inven;
}

Inventory* Player::GetInventory()
{
	return inventory;
}

void Player::SetTimer(TimeMoneyUi* time)
{
	this->timemoneyui = time;
}

TimeMoneyUi* Player::GetTimer()
{
	return timemoneyui;
}



