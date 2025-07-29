#include "stdafx.h"
#include "Player.h"
#include "NpcMgr.h"
#include "inventory.h"
#include "TimeMoneyUi.h"
#include "Item.h"
#include "Hoe.h"

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
			copyItem = new Hoe();
		}
		copyItem->SetItemInfo(this->item);
	}
}


void Player::Init()
{
	//Player Position���� �� ������ �޶����� �� ������ �ʱ� ��ġ�� �����ؼ� ����ؾ��մϴ�~ -�μ�-
	//SetPosition({100.f, 100.f});
	
	body.SetTarget(&bodySprite);
	hand.SetTarget(&handSprite);
	hat.SetTarget(&hatSprite);

	if(inventory)
		inventory->SetActive(false);
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
	ANI_CLIP_MGR.Load(ANIMATION_PATH"playerUseItem.csv");
	ANI_CLIP_MGR.Load(ANIMATION_PATH"playerUseItemHand.csv");

	bodySprite.setTexture(TEXTURE_MGR.Get("graphics/testC.png"));

	body.AddEvent("playeruseitem", 3, [this]() {
		useItem = false;
		body.Play(ANIMATION_PATH"playerforward.csv");
		hand.Play(ANIMATION_PATH"playerforwardhand.csv");
	});

	speed = 100;
}

void Player::Update(float dt)
{
	sortingOrder = GetPosition().y;
	std::cout << sortingOrder << std::endl;
	if (quickBarIdx != inventory->GetQuickBar()->GetQuickBarIdx()) {
		item = inventory->GetQuickBar()->GetItem();
		quickBarIdx = inventory->GetQuickBar()->GetQuickBarIdx();
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
	if (moveX != 0 || moveY != 0 || useItem) {
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
	window.draw(bodySprite);
	window.draw(handSprite);

	window.draw(hatSprite);
	if (item) {
		copyItem->Draw(window);
	}
	
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

void Player::PlayUseItemAnimation(sf::Vector2i dir)
{
	useItem = true;
	body.Play(ANIMATION_PATH"playerUseItem.csv");
	hand.Play(ANIMATION_PATH"playerUseItemHand.csv");
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



