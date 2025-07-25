#include "stdafx.h"
#include "NpcMgr.h"
#include "Player.h"
#include "TimeMoneyUi.h"

NpcMgr::NpcMgr(const std::string& name)
	: Collider(name)
{
}

void NpcMgr::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	npcSprite.setPosition(pos);
}

void NpcMgr::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	npcSprite.setRotation(rot);
}

void NpcMgr::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	npcSprite.setScale(s);
}

void NpcMgr::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	npcSprite.setOrigin(o);
}

void NpcMgr::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(npcSprite, preset);
	}
}

void NpcMgr::Init()
{
	Collider::Init();
	npcSprite.setPosition({ 70.f, 150.f });
}

void NpcMgr::Release()
{
}

void NpcMgr::Reset()
{
	npcSprite.setTexture(TEXTURE_MGR.Get("graphics/npcTest.png"));
}

void NpcMgr::Update(float dt)
{
	playerRect.setPosition(player->GetPosition());
	playerRect.setSize(player->GetGlobalBounds().getSize());

	player->SetPosition(playerRect.getPosition());
	if (!player->GetOpenInven())
	{
		if (IsCollidingPlayer(playerRect))
		{
			std::cout << "npcÃæµ¹" << std::endl;
			if (InputMgr::GetKeyDown(sf::Keyboard::Z))
			{
				player->ChangeOpenShop();
				player->ChangeisPlayer();
				timemoneyui->ChangeTimer();
				if (callback)
				{
					callback();
				}
			}
		}
	}
	if (player->GetOpenShop())
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
		{
			player->ChangeOpenShop();
			player->ChangeisPlayer();
			timemoneyui->ChangeTimer();
			if (callback)
			{
				callback();
			}
		}
	}


	sf::Vector2f playerPos = player->GetPosition();
}

void NpcMgr::Draw(sf::RenderWindow& window)
{
	window.draw(npcSprite);
}

bool NpcMgr::IsCollidingPlayer(sf::RectangleShape playerRect)
{
	sf::Vector2f npcPos = npcSprite.getPosition();
	sf::Vector2f npcSize = npcSprite.getGlobalBounds().getSize();

	sf::Vector2f rectPos = playerRect.getPosition();
	sf::Vector2f rectSize = playerRect.getGlobalBounds().getSize();

	return npcPos.x < rectPos.x + rectSize.x &&
		rectPos.x < npcPos.x + npcSize.x &&
		npcPos.y < rectPos.y + rectSize.y &&
		rectPos.y < npcPos.y + npcSize.y;
}

void NpcMgr::setCallBack(std::function<void()> cb)
{
	callback = cb;
}

sf::RectangleShape NpcMgr::GetPlayerRect()
{
	return playerRect;
}

sf::FloatRect NpcMgr::GetGlobalBounds()
{
	return npcSprite.getGlobalBounds();
}

void NpcMgr::SetTimer(TimeMoneyUi* time)
{
	this->timemoneyui = time;
}

TimeMoneyUi* NpcMgr::GetTimer()
{
	return timemoneyui;
}


