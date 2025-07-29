#pragma once
#include "Item.h"
class InUIItem : public Item
{
private:
	bool isDrag = false;
public:
	InUIItem(ItemInfo type);
	InUIItem() = default;
	~InUIItem() override = default;

	void Update(float dt) override;

	void DragItem();
	bool GetDrag() { return isDrag; };
};

