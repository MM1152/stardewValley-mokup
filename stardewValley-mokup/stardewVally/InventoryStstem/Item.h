#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "ItemInfo.h"

class Item : public GameObject
{
private:
	sf::Sprite itemSp;
	ItemInfo iteminfo;
	bool isDrag = false;
public:
	Item(ItemInfo type);
	Item() = default;
	~Item() override = default;

	// GameObject을(를) 통해 상속됨
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetPosition(const sf::Vector2f& pos) override;

	ItemInfo* GetItemInfo() { return &iteminfo; };
	void SetItemInfo(Item* item);
	void DragItem();
	bool GetDrag() { return isDrag; };
};

