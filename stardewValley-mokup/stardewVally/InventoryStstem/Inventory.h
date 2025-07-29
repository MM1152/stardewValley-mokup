#pragma once
#include "GameObject.h"
#include "Item.h"
#include "QuickBar.h"

class ItemSlot;
class Inventory : public GameObject
{
private:
	sf::RectangleShape inv_BackGround;
	
	std::string texId;

	std::vector<ItemSlot*> equipSlots;
	std::vector<ItemSlot*> unEquipSlots;

	int slotSize;

	
	QuickBar* quickBar = nullptr;
	//TEST
	InUIItem* item;
public:
	Inventory(const std::string& texId = "" , const std::string& name = "");
	~Inventory() override = default;

	// GameObject을(를) 통해 상속됨
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	bool SetItem(InUIItem* item);
	void SetQuickBar(QuickBar* quickBar) { this->quickBar = quickBar; };
	bool AddItem(const ItemInfo& info);
	
	QuickBar* GetQuickBar() { return quickBar; }
};

