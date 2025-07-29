#pragma once
#include "GameObject.h"
#include "Item.h"

class InGameItem : public Item
{
public:
	InGameItem(ItemInfo type);
	InGameItem() = default;
	~InGameItem() override = default;

	void Update(float dt) override;
	virtual void UseItem() {};
};

