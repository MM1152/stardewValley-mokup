#include "stdafx.h"
#include "ItemSlot.h"
#include "Item.h"

InUIItem* ItemSlot::dragItem = nullptr;

ItemSlot::ItemSlot(const std::string& texId, const std::string& fontId ,const std::string& name)
	:GameObject(name)
	,texId(texId)
	,fontId(fontId)
{
}

void ItemSlot::Init()
{
	slot.setSize({ 65,65 });
}

void ItemSlot::Release()
{
}

void ItemSlot::Reset()
{
	slot.setTexture(&TEXTURE_MGR.Get(texId));
}

void ItemSlot::Update(float dt)
{
	if (item && item->GetQuantity() <= 0) {
		item->SetItemInfo(nullptr);
		item = nullptr;
	}

	if (slot.getGlobalBounds().intersects(InputMgr::GetMouseUIRect())) {
		slot.setFillColor(sf::Color(187, 187, 187));

		if (InputMgr::GetMouseButtonDown(sf::Mouse::Left) && !dragItem) {
			if (item) {
				item->DragItem(true);
				dragItem = item;
				item = nullptr;
			}
		}
		else if (InputMgr::GetMouseButtonDown(sf::Mouse::Left) && dragItem) {
			if (GetItem()) {
				InUIItem* copy = GetItem();

				SetItem(dragItem);
				dragItem->DragItem(false);
				dragItem = copy;
				dragItem->DragItem(true);
			}
			else {
				SetItem(dragItem);
				dragItem->DragItem(false);
				dragItem = nullptr;
			}
		}
	}
	else {
		slot.setFillColor(sf::Color::White);
	}
}

void ItemSlot::Draw(sf::RenderWindow& window)
{
	window.draw(slot);
	if (item) {
		item->Draw(window);
	}
}

void ItemSlot::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	slot.setPosition(pos);
}

bool ItemSlot::SetItem(InUIItem* item)
{
	if (item && this->item && this->item->GetItemInfo()->itemId == item->GetItemInfo()->itemId) {
		this->item->PlusQuantity(1);
	}
	else {
		this->item = item;
		item->SetPosition({ GetPosition().x + slot.getSize().x / 2 , GetPosition().y + slot.getSize().y / 2 });
		item->SetItemInfo(item);
	}

	if (!item) {
		return false;
	}


	return true;
}
