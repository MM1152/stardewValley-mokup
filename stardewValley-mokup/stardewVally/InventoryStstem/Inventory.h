#pragma once
#include "GameObject.h"
#include "Item.h"
#include "QuickBar.h"
#include "DropItem.h"
#include "Crops.h"

class ItemSlot;
class Inventory : public GameObject
{
private:
	sf::RectangleShape inv_BackGround;
	
	std::string texId;

	std::vector<ItemSlot*> equipSlots;
	std::vector<ItemSlot*> unEquipSlots;

	int slotSize;

	DropItem* dropitem;
	Crops* crops;
	QuickBar* quickBar = nullptr;
	//TEST
	InUIItem* hoe;
	InUIItem* pick;
public:
	Inventory(const std::string& texId = ""  , const std::string& name = "");
	~Inventory() override = default;

	// GameObject��(��) ���� ��ӵ�
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	bool SetItem(InUIItem* item);
	void SetQuickBar(QuickBar* quickBar) { this->quickBar = quickBar; };
	bool AddItem(const ItemInfo& info);
	bool AddItem(DropItem* drop);

	QuickBar* GetQuickBar() { return quickBar; }
	void SetDropItem(DropItem* drop) { dropitem = drop; };
	void SetCrops(Crops* crop) { crops = crop; };
};

