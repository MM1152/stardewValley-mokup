#pragma once
#include "Item.h"
#include "DropItem.h"

class InUIItem : public Item
{
private:
	bool isDrag = false;
public:
	InUIItem(ItemInfo type);
	InUIItem(DropItem* drop);
	InUIItem() = default;
	~InUIItem() override = default;

	void Update(float dt) override;

	void DragItem();
	bool GetDrag() { return isDrag; };
};

