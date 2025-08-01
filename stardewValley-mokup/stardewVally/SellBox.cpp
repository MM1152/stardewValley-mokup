#include "stdafx.h"
#include "SellBox.h"
#include "Inventory.h"
#include "Player.h"
#include "InUIItem.h"
#include "TImeMoneyUi.h"

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
	boxRect.setFillColor(sf::Color(0, 0, 0, 0));

	boxBlockRect.setSize({currentBounds.width- 3, currentBounds.height-9});
	boxBlockRect.setPosition(sellBoxSprite.getPosition().x + 1.5, sellBoxSprite.getPosition().y + 5);
	//boxBlockRect.setFillColor(sf::Color(0,0,0,0));
	//boxBlockRect.setOutlineThickness(1.5);
	//boxBlockRect.setOutlineColor(sf::Color::Green);
}

void SellBox::Update(float dt)
{
	playerRect.setPosition(player->GetPosition());
	playerRect.setSize(player->GetGlobalBounds().getSize());

	player->SetPosition(playerRect.getPosition());

	if (!inventory->GetActive() && IsCollidingBox(playerRect))
	{
		if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
		{
			BoxOpen();
			inventory->SetActive(true);

			inventory->SetPosition({ FRAMEWORK.GetWindowSizeF().x / 2 - 400.f , FRAMEWORK.GetWindowSizeF().y / 2 - 300.f });
		}
	}
	if (inventory->GetActive() && InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		inventory->SetActive(false);
		BoxClosed();

		if (player)
		{
			player->SetIsPlayer(true);
		}
	}
}

void SellBox::Draw(sf::RenderWindow& window)
{
	window.draw(sellBoxSprite);
	window.draw(boxRect);
	//window.draw(boxBlockRect);
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

void SellBox::SellItem(Item& item)
{
	if (player == nullptr || timeMoneyUi == nullptr)
	{
		std::cout << "SellBox Player or TimeMoneyUi is null\n";
		return;
	}

	ItemInfo* itemInfo = item.GetItemInfo();

	int quantity = item.GetQuantity();
	int sellPrice = itemInfo->price * quantity;

	player->SetMoney(player->GetMoney() + sellPrice);
	timeMoneyUi->SettingMoney(player->GetMoney());

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

void SellBox::BoxOpen()
{
	isBoxOpen = true;
	std::cout << "SellBox opened\n";
}

void SellBox::BoxClosed()
{
	isBoxOpen = false;
}

bool SellBox::IsBoxOpen()
{
	return isBoxOpen;
}

bool SellBox::IsBoxClosed()
{
	return !isBoxOpen;
}