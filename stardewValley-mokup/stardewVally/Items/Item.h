#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "ItemInfo.h"
#include "DropItem.h"

class Player;
class DdropItem;
class Item : public GameObject
{
private:
	ItemInfo iteminfo;
	bool isUi;

protected:
	sf::Sprite itemSp;
	DropItem* dropitem;
	Player* player;
public:
	Item(ItemInfo type, bool isUi);
	Item(DropItem* drop, bool isUi);
	Item() = default;
	~Item() override = default;

	// GameObject을(를) 통해 상속됨
	void Init() override;
	void Release() override;
	void Reset() override;
	void Draw(sf::RenderWindow& window) override;

	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetPosition(const sf::Vector2f& pos) override;
	virtual void SetOrigin(Origins preset) override;
	virtual void SetOrigin(const sf::Vector2f& o) override;

	ItemInfo* GetItemInfo() { return &iteminfo; };
	void SetItemInfo(Item* item);
	void SetPlayer(Player* player) { this->player = player; };
	void SetDropItem(DropItem* drop) { dropitem = drop; };
};

