#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "ItemInfo.h"

class Player;
class Item : public GameObject
{
private:
	ItemInfo iteminfo;
	bool isUi;
protected:
	sf::Sprite itemSp;
	Player* player;

	Item* parentItem = nullptr;
	int quantity = 1;
public:
	Item(ItemInfo type, bool isUi);
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

	int GetQuantity() { return quantity; };
	virtual void PlusQuantity(int quantity) { this->quantity += quantity; };

	virtual bool UseItem() { return false; };
};

