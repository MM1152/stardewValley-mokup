#include "stdafx.h"
#include "Player.h"
#include "NpcMgr.h"
#include "inventory.h"
#include "TimeMoneyUi.h"
#include "TileMap.h"
#include "Map.h"

#include "Item.h"
#include "Hog.h"

Player::Player(const std::string name)
	:Collider(name)
{
}

void Player::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	bodySprite.setPosition(pos);
	handSprite.setPosition(pos);
	hatSprite.setPosition(pos);
}

void Player::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	bodySprite.setRotation(rot);
	handSprite.setRotation(rot);
	hatSprite.setRotation(rot);
}

void Player::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	bodySprite.setScale(s);
	handSprite.setScale(s);
	hatSprite.setScale(s);
}

void Player::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	bodySprite.setOrigin(o);
}
void Player::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(bodySprite, preset);
	}
}

void Player::SetItem(Item* item)
{
	if (this->item) {
		delete copyItem;
	}

	this->item = item;

	if (this->item) {
		if (this->item->GetItemInfo()->itemId == "hoe") {
			copyItem = new Hog();
		}
		copyItem->SetItemInfo(this->item);
	}
}

void Player::Init()
{
	seedGuideRect.setSize({16.f, 16.f});
	seedGuideRect.setFillColor(sf::Color(0, 255, 0, 100));
	seedGuideRect.setOutlineColor(sf::Color(102, 255, 0, 135));
	seedGuideRect.setOutlineThickness(3);
	seedGuideRect.setOrigin(Utils::SetOrigin(bodySprite, Origins::MC));
	seedGuideRect.setPosition(bodySprite.getPosition());

	if (inventory)
	{
	
	body.SetTarget(&bodySprite);
	hand.SetTarget(&handSprite);
	hat.SetTarget(&hatSprite);

	if(inventory)
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
	ANI_CLIP_MGR.Load(ANIMATION_PATH"hat1left.csv");
	ANI_CLIP_MGR.Load(ANIMATION_PATH"hat1backward.csv");
	ANI_CLIP_MGR.Load(ANIMATION_PATH"hat1forward.csv");
	ANI_CLIP_MGR.Load(ANIMATION_PATH"playerleft.csv");
	ANI_CLIP_MGR.Load(ANIMATION_PATH"playerforward.csv");
	ANI_CLIP_MGR.Load(ANIMATION_PATH"playerbackward.csv");
	ANI_CLIP_MGR.Load(ANIMATION_PATH"playerlefthand.csv");
	ANI_CLIP_MGR.Load(ANIMATION_PATH"playerforwardhand.csv");
	ANI_CLIP_MGR.Load(ANIMATION_PATH"playerbackwardhand.csv");

	bodySprite.setTexture(TEXTURE_MGR.Get("graphics/testC.png"));

	speed = 100;
}

void Player::Update(float dt)
{
	if (quickBarIdx != inventory->GetQuickBar()->GetQuickBarIdx()) {
		item = inventory->GetQuickBar()->GetItem();
		if (item) {
			SetItem(item);
			copyItem->Init();
			copyItem->Reset();
			copyItem->SetPlayer(this);
		}
	}
	
	if (item) {
		copyItem->Update(dt);

		if (InputMgr::GetKeyDown(sf::Keyboard::Z)) {
			copyItem->UseItem();
		}
	}

	

	sf::Vector2f movement = { 0.f, 0.f };
	
	float moveX = InputMgr::GetAxisRaw(Axis::Horizontal);
	float moveY = InputMgr::GetAxisRaw(Axis::Vertical);

	PlayMoveAnimation({moveX , moveY});
	if (moveX != 0 || moveY != 0) {
		body.Update(dt);
		hand.Update(dt);
		
	}
	
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

  /*  if (InputMgr::GetKeyDown(sf::Keyboard::E)) {
        inventory->SetActive(!inventory->GetActive());
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

	sf::Vector2f playerCenter = bodySprite.getPosition();
	sf::Vector2f offSet = (sf::Vector2f)lookDir * 16.f;

	float rowX = playerCenter.x + offSet.x;
	float rowY = playerCenter.y + offSet.y;

	int tileX = ((int)rowX / 16) * 16;
	int tileY = ((int)rowY / 16) * 16;

	seedGuideRect.setPosition({ (float)tileX, (float)tileY});


}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(handSprite);
	window.draw(bodySprite);
	window.draw(hatSprite);
	if (item) {
		copyItem->Draw(window);
	}

	window.draw(seedGuideRect);
}

void Player::PlayMoveAnimation(sf::Vector2f dir)
{
	if (prevDir == dir) return;

	prevDir = dir;

	if (dir.x > 0) {
		body.Play(ANIMATION_PATH"playerleft.csv");
		hand.Play(ANIMATION_PATH"playerlefthand.csv");
		hat.Play(ANIMATION_PATH"hat1left.csv");
		SetScale({ 1,1 });
		lookDir = { 1 , 0 };
	}
	else if (dir.x < 0) {
		body.Play(ANIMATION_PATH"playerleft.csv");
		hand.Play(ANIMATION_PATH"playerlefthand.csv");
		hat.Play(ANIMATION_PATH"hat1left.csv");
		SetScale({ -1,1 });
		lookDir = { -1 , 0 };
	}
	else if (dir.y > 0) {
		body.Play(ANIMATION_PATH"playerforward.csv");
		hand.Play(ANIMATION_PATH"playerforwardhand.csv");
		hat.Play(ANIMATION_PATH"hat1forward.csv");
		lookDir = { 0 , 1 };
	}
	else if (dir.y < 0) {
		body.Play(ANIMATION_PATH"playerbackward.csv");
		hand.Play(ANIMATION_PATH"playerbackwardhand.csv");
		hat.Play(ANIMATION_PATH"hat1backward.csv");
		lookDir = { 0 , -1 };
	}
	SetOrigin(Origins::BC);
	sf::FloatRect center = bodySprite.getLocalBounds();
	handSprite.setOrigin({center.width / 2 + 1.5f, center.height / 2 + 5.9f});
	hatSprite.setOrigin({ center.width / 2 + 3.f, center.height / 2 + 20.f });
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



