#include "stdafx.h"
#include "Player.h"
#include "NpcMgr.h"
#include "inventory.h"
#include "TimeMoneyUi.h"
#include "TileMap.h"
#include "Map.h"
#include "Item.h"
#include "Hoe.h"
#include "Seeds.h"
#include "Crops.h"
#include "Pick.h"
#include "SellBox.h"
#include "DialogueBox.h"

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
	shirtSprite.setPosition(pos);
	bound.setPosition(pos);
}

void Player::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	bodySprite.setRotation(rot);
	handSprite.setRotation(rot);
	hatSprite.setRotation(rot);
	shirtSprite.setRotation(rot);
	bound.setRotation(rot);
}

void Player::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	bodySprite.setScale(s);
	handSprite.setScale(s);
	hatSprite.setScale(s);
	shirtSprite.setScale(s);
	bound.setScale(s);
}

void Player::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	bodySprite.setOrigin(o);
	bound.setOrigin(o);
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
		ItemInfo info = itemDataMgr::Instance().GetItem(this->item->GetItemInfo()->itemId);
		if (this->item->GetItemInfo()->itemId == "hoe") {
			copyItem = new Hoe();
		}
		else if (this->item->GetItemInfo()->itemId == "parsnip_seeds")
		{
			copyItem = new Seeds();
		}
		else if (this->item->GetItemInfo()->itemId == "cauliflower_seeds")
		{
			copyItem = new Seeds();
		}
		else if (this->item->GetItemInfo()->itemId == "potato_seeds")
		{
			copyItem = new Seeds();
		}
		else if (this->item->GetItemInfo()->itemId == "garlic_seeds")
		{
			copyItem = new Seeds();
		}
		else if (this->item->GetItemInfo()->itemId == "pick")
		{
			copyItem = new Pick();
		}
		else {
			copyItem = new InGameItem();
		}

		copyItem->SetPlayer(this);
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

	bound.setSize({ 16.f, 24.f });
	bound.setFillColor(sf::Color::Transparent);
	bound.setPosition(GetPosition());

	if (inventory)
	{
	
	body.SetTarget(&bodySprite);
	hand.SetTarget(&handSprite);
	hat.SetTarget(&hatSprite);
	shirt.SetTarget(&shirtSprite);

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
	prevDir = { -1,-1 };
	ANI_CLIP_MGR.Load(ANIMATION_PATH"hat1left.csv");
	ANI_CLIP_MGR.Load(ANIMATION_PATH"hat1backward.csv");
	ANI_CLIP_MGR.Load(ANIMATION_PATH"hat1forward.csv");
	ANI_CLIP_MGR.Load(ANIMATION_PATH"shirtleft.csv");
	ANI_CLIP_MGR.Load(ANIMATION_PATH"shirtbackward.csv");
	ANI_CLIP_MGR.Load(ANIMATION_PATH"shirtforward.csv");
	ANI_CLIP_MGR.Load(ANIMATION_PATH"playerleft.csv");
	ANI_CLIP_MGR.Load(ANIMATION_PATH"playerforward.csv");
	ANI_CLIP_MGR.Load(ANIMATION_PATH"playerbackward.csv");
	ANI_CLIP_MGR.Load(ANIMATION_PATH"playerlefthand.csv");
	ANI_CLIP_MGR.Load(ANIMATION_PATH"playerforwardhand.csv");
	ANI_CLIP_MGR.Load(ANIMATION_PATH"playerbackwardhand.csv");
	ANI_CLIP_MGR.Load(ANIMATION_PATH"playerUseItemFront.csv");
	ANI_CLIP_MGR.Load(ANIMATION_PATH"playerUseItemLeft.csv");
	ANI_CLIP_MGR.Load(ANIMATION_PATH"playerUseItemBack.csv");
	ANI_CLIP_MGR.Load(ANIMATION_PATH"playerUseItemHandFront.csv");
	ANI_CLIP_MGR.Load(ANIMATION_PATH"playerUseItemHandLeft.csv");
	ANI_CLIP_MGR.Load(ANIMATION_PATH"playerUseItemHandBack.csv");


	body.Play(ANIMATION_PATH"playerforward.csv");
	hand.Play(ANIMATION_PATH"playerforwardhand.csv");
	hat.Play(ANIMATION_PATH"hat1forward.csv");
	shirt.Play(ANIMATION_PATH"shirtforward.csv");


	hand.AddEvent("playeruseitemhandleft", 3, [this]() {
		sf::FloatRect center = bodySprite.getLocalBounds();
		handSprite.setOrigin({ center.width / 2 + 2.f, center.height / 2 + 5.f });
		});

	hand.AddEvent("playeruseitemhandrigth", 3, [this]() {
		sf::FloatRect center = bodySprite.getLocalBounds();
		handSprite.setOrigin({ center.width / 2 + 2.f, center.height / 2 + 5.f });
		});

	body.AddEvent("playeruseitem", 3, [this]() {
		isPlayer = true;
		useItem = false;
		body.Play(ANIMATION_PATH"playerforward.csv");
		hand.Play(ANIMATION_PATH"playerforwardhand.csv");
	});

	body.AddEvent("playeruseitemback", 3, [this]() {
		isPlayer = true;
		useItem = false;
		body.Play(ANIMATION_PATH"playerbackward.csv");
		hand.Play(ANIMATION_PATH"playerbackwardhand.csv");
	});

	body.AddEvent("playeruseitemleft", 3, [this]() {
		isPlayer = true;
		useItem = false;
		body.Play(ANIMATION_PATH"playerleft.csv");
		hand.Play(ANIMATION_PATH"playerlefthand.csv");
	});



	speed = 100;
	SetOrigin(Origins::BC);
	sf::FloatRect center = bodySprite.getLocalBounds();
	handSprite.setOrigin({ center.width / 3 + 4.5f, center.height / 2 + 5.f });
	hatSprite.setOrigin({ center.width / 2 + 3.3f, center.height / 2 + 19.f });
	shirtSprite.setOrigin({ center.width / 3 + 0.45f, center.height / 2 + 1.9f });


	sf::FloatRect currentBounds = bodySprite.getGlobalBounds();
	bound.setSize({ currentBounds.width - 5, currentBounds.height -20});
	bound.setOrigin(Utils::SetOrigin(bound, Origins::BC));
	bound.setFillColor(sf::Color(0, 0, 255, 100));
	bound.setPosition(GetPosition());
}

void Player::Update(float dt)
{
	sortingOrder = GetPosition().y;

	if (item != inventory->GetQuickBar()->GetItem() || quickBarIdx != inventory->GetQuickBar()->GetQuickBarIdx()) {
		item = inventory->GetQuickBar()->GetItem();
		quickBarIdx = inventory->GetQuickBar()->GetQuickBarIdx();
		if (item) {
			SetItem(item);
			copyItem->Init();
			copyItem->Reset();
			copyItem->SetPlayer(this);
		}
	}
	
	if (item) 
	{
		copyItem->Update(dt);
		if (InputMgr::GetKeyDown(sf::Keyboard::Z) || 
			InputMgr::GetMouseButtonDown(sf::Mouse::Left)) 
		{
			copyItem->UseItem();	
		}
	
	}

	sf::Vector2f movement = { 0.f, 0.f };
	
	float moveX = InputMgr::GetAxisRaw(Axis::Horizontal);
	float moveY = InputMgr::GetAxisRaw(Axis::Vertical);
	

	if (moveX != 0 || moveY != 0 || useItem) {
		hand.Update(dt);
		body.Update(dt);
	}

	if (isPlayer)
	{
		PlayMoveAnimation({ moveX , moveY });

		movement.x = moveX * speed * dt;
		movement.y = moveY * speed * dt;
		sf::Vector2f moveOffset(movement.x, movement.y);

		bound.setPosition(bodySprite.getPosition());

		Collider::areaBlocked(position, *this, moveOffset);
	}
	
	if (!openShop)
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::E))
		{
			if (!openInven) 
			{
				SetIsPlayer(false);
				openInven = true;
				inventory->SetActive(true);
			}
			else 
			{
				SetIsPlayer(true); 
				openInven = false;
				inventory->SetActive(false);
			}

			timemoneyui->ChangeTimer();
		}
	}

	// openInven > Escape out
	if (openInven)
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
		{
			SetIsPlayer(true);
			openInven = false;
			inventory->SetActive(false);
			timemoneyui->ChangeTimer();
		}
	}

	if (!openShop && !openInven) //&& fainting)
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::F10))
		{
			timemoneyui->Changeth();
			isPlayer = true;
			fainting = false;
			growup = true;
		}
	} 

	//if (!openShop && !openInven && dialogueBox && !dialogueBox->IsActive() && !npcMgr->GetIsTalking() && !isPlayer)
	//{
	//	SetIsPlayer(true);
	//}

	sf::Vector2f playerCenter = bodySprite.getPosition();
	sf::Vector2f offSet = (sf::Vector2f)lookDir * 16.f;

	float rowX = playerCenter.x + offSet.x;
	float rowY = playerCenter.y + offSet.y;

	int tileX = (int)rowX / 16; 
	int tileY = (int)rowY / 16;

	if (map)
	{
		int cellIdx = map->GetCellIndex({ (float)rowX, (float)rowY}, 0);
		if (cellIdx >= map->GetCellDatas(0).size()) return;
		if (InputMgr::GetKeyDown(sf::Keyboard::R)) {
			std::cout << cellIdx << std::endl;
		}
		if (CanUseItemOnTile(cellIdx)) 
		{
			seedGuideRect.setFillColor(sf::Color(0, 255, 0, 100));
			seedGuideRect.setOutlineColor(sf::Color(102, 255, 0, 135));
		}
		else 
		{
			seedGuideRect.setFillColor(sf::Color(255, 0, 0, 100));
			seedGuideRect.setOutlineColor(sf::Color(255, 50, 50, 135));
		}

		seedGuideRect.setPosition(map->GetCell(cellIdx, 0).cellPosition[0]);
	}
	
}

void Player::Draw(sf::RenderWindow& window)
{
	if (prevDir.y == -1) {
		if (item) {
			copyItem->Draw(window);
		}
		window.draw(handSprite);
		window.draw(bodySprite);
		window.draw(hatSprite);
		window.draw(shirtSprite);
	}
	else {
		window.draw(bodySprite);
		window.draw(handSprite);
		window.draw(hatSprite);
		window.draw(shirtSprite);
		if (item) {
			copyItem->Draw(window);
		}
	}
	

	window.draw(seedGuideRect);
}

void Player::PlayMoveAnimation(sf::Vector2f dir)
{
	if (prevDir == dir) return;
	if (dir.x != 0 || dir.y != 0) {
		prevDir = dir;
	}
	
	sf::FloatRect center = bodySprite.getLocalBounds();
	if (dir.x > 0) {
		body.Play(ANIMATION_PATH"playerleft.csv");
		hand.Play(ANIMATION_PATH"playerlefthand.csv");
		hat.Play(ANIMATION_PATH"hat1left.csv");
		shirt.Play(ANIMATION_PATH"shirtleft.csv");

		SetScale({ 1,1 });
		handSprite.setOrigin({ center.width / 3 + 4.5f, center.height / 2 + 5.f });
		lookDir = { 1 , 0 };
	}
	else if (dir.x < 0) {
		body.Play(ANIMATION_PATH"playerleft.csv");
		hand.Play(ANIMATION_PATH"playerlefthand.csv");
		hat.Play(ANIMATION_PATH"hat1left.csv");
		shirt.Play(ANIMATION_PATH"shirtleft.csv");

		SetScale({ -1,1 });
		handSprite.setOrigin({ center.width / 3 + 4.75f, center.height / 2 + 5.f });
		lookDir = { -1 , 0 };
	}
	else if (dir.y > 0) {
		body.Play(ANIMATION_PATH"playerforward.csv");
		hand.Play(ANIMATION_PATH"playerforwardhand.csv");
		hat.Play(ANIMATION_PATH"hat1forward.csv");
		shirt.Play(ANIMATION_PATH"shirtforward.csv");

		SetScale({ 1,1 });
		handSprite.setOrigin({ center.width / 3.f + 4.5f, center.height / 2 + 5.f });
		
		lookDir = { 0 , 1 };
	}
	else if (dir.y < 0) {
		body.Play(ANIMATION_PATH"playerbackward.csv");
		hand.Play(ANIMATION_PATH"playerbackwardhand.csv");
		hat.Play(ANIMATION_PATH"hat1backward.csv");
		shirt.Play(ANIMATION_PATH"shirtbackward.csv");
		SetScale({ 1,1 });
		lookDir = { 0 , -1 };
		handSprite.setOrigin({ (center.width + center.left) / 3 + 3.75f, center.height / 2 + 5.9f });
	}
	SetOrigin(Origins::BC);

	hatSprite.setOrigin({ center.width / 2 + 3.3f, center.height / 2 + 19.f });
	
}

void Player::PlayUseItemAnimation(sf::Vector2i dir)
{
	useItem = true;
	isPlayer = false;
	sf::FloatRect center = bodySprite.getLocalBounds();

	if (dir.x == 1) {
		body.Play(ANIMATION_PATH"playerUseItemLeft.csv");
		hand.Play(ANIMATION_PATH"playerUseItemHandLeft.csv");
		handSprite.setOrigin({ (center.width + center.left) / 3 + 4.5f, center.height / 2 + 15.f });
		SetScale({ 1,1 });
	}
	else if (dir.x == -1) {
		body.Play(ANIMATION_PATH"playerUseItemLeft.csv");
		hand.Play(ANIMATION_PATH"playerUseItemHandLeft.csv");
		handSprite.setOrigin({ (center.width + center.left) / 3 + 4.75f, center.height / 2 + 15.f });
		SetScale({ -1,1 });
	}
	else if (dir.y == 1) {
		body.Play(ANIMATION_PATH"playerUseItemFront.csv");
		hand.Play(ANIMATION_PATH"playerUseItemHandFront.csv");
		
	}
	else if (dir.y == -1) {
		body.Play(ANIMATION_PATH"playerUseItemBack.csv");
		hand.Play(ANIMATION_PATH"playerUseItemHandBack.csv");
	}
	
}

bool Player::CanUseItemOnTile(int tileIdx)
{
	if (!item || !map)
		return false;

	const ItemInfo* info = item->GetItemInfo();
	int usableLayer = info->usableLayer;

	CheckCellData cellData = map->SequentialGetCell(tileIdx);
	const auto& usable = info->usableTiles;

	if (cellData.layer != usableLayer)
		return false;

	return std::find(usable.begin(), usable.end(), cellData.idx) != usable.end();
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

void Player::SetDialogueBox(DialogueBox* dialogue)
{
	dialogueBox = dialogue;
}

DialogueBox* Player::GetDialogueBox()
{
	return dialogueBox;
}

