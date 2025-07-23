#include "stdafx.h"
#include "Inventory.h"
#include "ItemSlot.h"

Inventory::Inventory(const std::string& texId, const std::string& name)
	:GameObject(name)
	, texId(texId)
{
}

void Inventory::Init()
{
	inv_BackGround.setSize({ 45 * 12 , 300 });
	inv_BackGround.setPosition({ FRAMEWORK.GetWindowSizeF().x / 2 - 400.f , FRAMEWORK.GetWindowSizeF().y / 2});
	
	slotSize = 24;
	for (int i = 0; i < 12; i++) {
		ItemSlot* itemSlot = new ItemSlot();
		itemSlot->Init();
		itemSlot->Reset();

		itemSlot->SetPosition({ inv_BackGround.getPosition().x + 3.f + i * 45 , inv_BackGround.getPosition().y  + 10.f});
		equipSlots.push_back(itemSlot);
	}

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < slotSize / 2; j++) {
			ItemSlot* itemSlot = new ItemSlot();
			itemSlot->Init();
			itemSlot->Reset();
			
			itemSlot->SetPosition({ inv_BackGround.getPosition().x + 3.f + j * 45 , inv_BackGround.getPosition().y + 110.f + (80.f * i)});
			unEquipSlots.push_back(itemSlot);
		}
	}
}

void Inventory::Release()
{
}

void Inventory::Reset()
{
}

void Inventory::Update(float dt)
{
	for (auto slot : equipSlots) {
		slot->Update(dt);
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
bool Inventory::SetItem(Item* item)
{
	for (int i = 0; i < slotSize; i++) {
		if (!unEquipSlots[i]->IsSetting()) {
			unEquipSlots[i]->SetItem(item);
			return true;
		}
	}

	return false;
}
