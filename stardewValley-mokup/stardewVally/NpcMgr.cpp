#include "stdafx.h"
#include "NpcMgr.h"
#include "Player.h"

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
	npcSprite.setPosition({0.f, 0.f});
	npcTalkSprite.setPosition({ -50.f, -50.f });
}

void NpcMgr::Release()
{
}

void NpcMgr::Reset()
{
	npcSprite.setTexture(TEXTURE_MGR.Get("graphics/npcTest.png"));
	npcTalkSprite.setTexture(TEXTURE_MGR.Get("graphics/npcTalk.png"));
}

void NpcMgr::Update(float dt)
{
	std::srand(static_cast<unsigned>(std::time(nullptr)));

	float axisX = (std::rand() % 3) - 1;
	float axisY = (std::rand() % 3) - 1;

	direction = sf::Vector2f(axisX, axisY);

	sf::Vector2f moveOffset = { axisX * speed * dt, axisY * speed * dt};

	if (isNpcMove)
	{
		Collider::areaBlocked(position, npcTalkSprite, moveOffset);
		npcTalkSprite.setPosition(position);
	}

	playerRect.setPosition(player->GetPosition());
	playerRect.setSize(player->GetGlobalBounds().getSize());

	player->SetPosition(playerRect.getPosition());

	if (IsCollidingPlayer(playerRect))
	{
		std::cout << "npc충돌" << std::endl;
		if (InputMgr::GetKeyDown(sf::Keyboard::Z)) //function's address 
		{
			if (callback)
			{
				callback();
			}
		}
	}

	if (IsTalkCollidingPlayer(playerRect))
	{
		std::cout << "talk npc 충돌" << std::endl;
		if (InputMgr::GetKeyDown(sf::Keyboard::Z))
		{
			isNpcMove = false;
			if (talkCallback)
				talkCallback(); 
		} 
		else if (!talkCallback)
		{
			isNpcMove = true;
		}
	}

	sf::Vector2f playerPos = player->GetPosition();
}

void NpcMgr::Draw(sf::RenderWindow& window)
{
	window.draw(npcSprite);
	window.draw(npcTalkSprite);
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

bool NpcMgr::IsTalkCollidingPlayer(sf::RectangleShape rect)
{
	sf::Vector2f npcPos = npcTalkSprite.getPosition();
	sf::Vector2f npcSize = npcTalkSprite.getGlobalBounds().getSize();

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

void NpcMgr::setTalkCallBack(std::function<void()> cb)
{
	talkCallback = cb;
}

sf::RectangleShape NpcMgr::GetPlayerRect()
{
	return playerRect;
}

sf::FloatRect NpcMgr::GetGlobalBounds()
{
	return npcSprite.getGlobalBounds();
}




