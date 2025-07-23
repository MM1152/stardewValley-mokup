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
	inv_BackGround.setSize({ 45 * 12 + 20.f , 300 });
	inv_BackGround.setPosition({ FRAMEWORK.GetWindowSizeF().x / 2 - 400.f , FRAMEWORK.GetWindowSizeF().y / 2});
	
	slotSize = 24;
	for (int i = 0; i < 12; i++) {
		ItemSlot* itemSlot = new ItemSlot(INVEN_IMG_PATH"ItemSlot.png");
		itemSlot->Init();

		itemSlot->SetPosition({ inv_BackGround.getPosition().x + 10.f + i * 45 , inv_BackGround.getPosition().y  + 20.f});
		equipSlots.push_back(itemSlot);
	}

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < slotSize / 2; j++) {
			ItemSlot* itemSlot = new ItemSlot(INVEN_IMG_PATH"ItemSlot.png");
			itemSlot->Init();
			itemSlot->SetPosition({ inv_BackGround.getPosition().x + 10.f + j * 45 , inv_BackGround.getPosition().y + 110.f + (80.f * i)});
			
			unEquipSlots.push_back(itemSlot);
		}
	}
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
}

void Inventory::Update(float dt)
{
	for (auto slot : equipSlots) {
		slot->Update(dt);
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
