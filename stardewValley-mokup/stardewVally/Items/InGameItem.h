#pragma once
#include "GameObject.h"
#include "Item.h"

class InGameItem : public Item
{
protected:
public:
	InGameItem(ItemInfo type);
	InGameItem() = default;
	~InGameItem() override = default;

	void Update(float dt) override;
	bool UseItem() override;
};

