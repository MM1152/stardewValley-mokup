#pragma once
#include "GameObject.h"
#include "Item.h"

class ItemSlot;
class Inventory : public GameObject
{
private:
	sf::RectangleShape inv_BackGround;
	
	std::string texId;

	std::vector<ItemSlot*> equipSlots;
	std::vector<ItemSlot*> unEquipSlots;

	int slotSize;

	//TEST
	Item item;
public:
	Inventory(const std::string& texId = "" , const std::string& name = "");
	~Inventory() override = default;

	// GameObject을(를) 통해 상속됨
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	bool SetItem(Item* item);
};

