#include "stdafx.h"
#include "ItemSlot.h"
#include "Item.h"

InUIItem* ItemSlot::dragItem = nullptr;

ItemSlot::ItemSlot(const std::string& texId, const std::string& name)
	:GameObject(name)
	,texId(texId)
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
	if (slot.getGlobalBounds().intersects(InputMgr::GetMouseUIRect())) {
		slot.setFillColor(sf::Color(187, 187, 187));

		if (InputMgr::GetMouseButtonDown(sf::Mouse::Left)) {
			if (item) {
				item->DragItem();
				dragItem = item;
				item = nullptr;
			}
		}
		if (InputMgr::GetMouseButtonUp(sf::Mouse::Left) && dragItem != nullptr) {
			SetItem(dragItem);
			dragItem = nullptr;
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
	this->item = item;
	if (!item) {
		return false;
	}

	item->SetItemInfo(item);
	item->SetPosition({ GetPosition().x + slot.getSize().x / 2 , GetPosition().y + slot.getSize().y / 2 });

	return true;
}
