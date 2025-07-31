#pragma once
#include "Item.h"
#include "DropItem.h"

class InUIItem : public Item
{
private:
	bool isDrag = false;

	std::string fontId;
	sf::Text quantityText;

public:
	InUIItem(ItemInfo type);
	InUIItem(DropItem* drop);
	InUIItem() = default;
	~InUIItem() override = default;

	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void DragItem(bool isDrag);
	bool GetDrag() { return isDrag; };
	void PlusQuantity(int quantity) override;

	bool UseItem() override;
};

