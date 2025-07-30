#include "stdafx.h"
#include "Inventory.h"
#include "ItemSlot.h"
#include "QuickBar.h"

Inventory::Inventory(const std::string& texId, const std::string& name)
	:GameObject(name)
	, texId(texId)
{
	sortingOrder = 2;
}

void Inventory::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;

	inv_BackGround.setSize({ 65 * 12 + 45.f , 270 });
	inv_BackGround.setPosition({ FRAMEWORK.GetWindowSizeF().x / 2 - 400.f , FRAMEWORK.GetWindowSizeF().y / 2 - 300.f});

	slotSize = 24;
	for (int i = 0; i < 12; i++) {
		ItemSlot* itemSlot = new ItemSlot(INVEN_IMG_PATH"ItemSlot.png");
		itemSlot->Init();

		itemSlot->SetPosition({ inv_BackGround.getPosition().x + i * 65 + 20.f, inv_BackGround.getPosition().y  + 20.f});
		equipSlots.push_back(itemSlot); //slot position
	}

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < slotSize / 2; j++) {
			ItemSlot* itemSlot = new ItemSlot(INVEN_IMG_PATH"ItemSlot.png");
			itemSlot->Init();
			itemSlot->SetPosition({ inv_BackGround.getPosition().x + j * 65 + 20.f, inv_BackGround.getPosition().y + 100.f + (65.f * i)});
			
			unEquipSlots.push_back(itemSlot);
		}
	}

	//ItemInfo sword = { "galaxy_sword" ,  ITEM_IMG_PATH"galaxy_sword.png" /*ItemType::EquipMent*/};
	hoe = new InUIItem(itemDataMgr::Instance().GetItem("hoe"));
	hoe->Init();
	pick = new InUIItem(itemDataMgr::Instance().GetItem("pick"));
	pick->Init();
}

void Inventory::Release()
{

}

void Inventory::Reset()
{
	inv_BackGround.setTexture(&TEXTURE_MGR.Get(texId));

	for (auto slot : equipSlots) {
		slot->Reset();
		
	}
	for (auto slot : unEquipSlots) {
		slot->Reset();
	}
	hoe->Reset();
	pick->Reset();
	SetItem(hoe);
	SetItem(pick);
}

void Inventory::Update(float dt)
{
	for (int i = 0; i < equipSlots.size(); i++) {
		equipSlots[i]->Update(dt);
		quickBar->SetItem(equipSlots[i]->GetItem(), i);
	}
	for (auto slot : unEquipSlots) {
		slot->Update(dt);
	}
	if (ItemSlot::dragItem) {
		ItemSlot::dragItem->Update(dt);
	}
	
}

void Inventory::Draw(sf::RenderWindow& window)
{
	window.draw(inv_BackGround);

	for (auto slot : equipSlots) {
		slot->Draw(window);
	}

	for (auto slot : unEquipSlots) {
		slot->Draw(window);
	}

	if (ItemSlot::dragItem) {
		ItemSlot::dragItem->Draw(window);
	}

}

//가방 돌면서 비어있는 슬릇확인, 비어있는 곳은 true 없으면 false
bool Inventory::SetItem(InUIItem* item)
{
	for (int i = 0; i < slotSize; i++) {
		if (!unEquipSlots[i]->IsSetting()) {
			unEquipSlots[i]->SetItem(item);
			return true;
		}
	}

	return false;
}

bool Inventory::AddItem(const ItemInfo& info)
{
	InUIItem* newItem = new InUIItem(info);
	newItem->Init();
	if (newItem->GetItemInfo()->quantity == 1) {
		for (ItemSlot* slot : equipSlots) {
			if (!slot->IsSetting())
			{
				slot->SetItem(newItem);
				return true;
			}
		}
		for (ItemSlot* slot : unEquipSlots)
		{
			if (!slot->IsSetting())
			{
				slot->SetItem(newItem);
				return true;
			}
		}
	}
	else {
		int emptySlot = -1;
		int cnt = 0;
		for (ItemSlot* slot : equipSlots)
		{
			if (slot->IsSetting() && slot->GetItem()->GetItemInfo()->itemId == info.itemId) {
				slot->SetItem(newItem);
				return true;
			}
			if (!slot->IsSetting() && emptySlot == -1)
			{
				emptySlot = cnt;
			}
			cnt++;
		}
		if(emptySlot != -1){
			equipSlots[emptySlot]->SetItem(newItem);
			return true;
		}
		for (ItemSlot* slot : unEquipSlots)
		{
			if (slot->IsSetting() && slot->GetItem()->GetItemInfo()->itemId == info.itemId) {
				slot->SetItem(newItem);
				return true;
			}
			if (!slot->IsSetting() && emptySlot == -1 )
			{
				emptySlot = cnt;
			}
			cnt++;
		}

		if (emptySlot != -1) {
			unEquipSlots[emptySlot]->SetItem(newItem);
			return true;
		}
	}
	

	delete newItem;
	return false;
}
