#include "stdafx.h"
#include "Player.h"
#include "NpcMgr.h"
#include "inventory.h"


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

void Player::Init()
{
	SetPosition({-50.f, -50.f});
	Collider::Init();
}

void Player::Release()
{
}

void Player::Reset()
{
	sprite.setTexture(TEXTURE_MGR.Get("graphics/testC.png"));
}

void Player::Update(float dt)
{
	sf::Vector2f movement = { 0.f, 0.f };

	float moveX = InputMgr::GetAxis(Axis::Horizontal);
	float moveY = InputMgr::GetAxis(Axis::Vertical);

	movement.x = moveX * speed * dt;
	movement.y = moveY * speed * dt;

	std::vector<sf::RectangleShape> shapes;

	sf::Vector2f moveOffset(movement.x, movement.y);

	Collider::areaBlocked(position, sprite, moveOffset);

    /*if (npcMgr != nullptr)
    {
        sf::Vector2f npcPos = npcMgr->GetPosition();
        sf::Vector2f npcSize = npcMgr->GetGlobalBounds().getSize();
        sf::Vector2f playerSize = sprite.getGlobalBounds().getSize();

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

    if (InputMgr::GetKeyDown(sf::Keyboard::E)) {
        inventory->SetActive(!inventory->GetActive());
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



