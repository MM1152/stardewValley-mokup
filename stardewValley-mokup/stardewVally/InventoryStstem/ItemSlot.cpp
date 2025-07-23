#include "stdafx.h"
#include "ItemSlot.h"
#include "Item.h"

Item* ItemSlot::dragItem = nullptr;

ItemSlot::ItemSlot(const std::string& texId, const std::string& name)
	:GameObject(name)
	,texId(texId)
{
}

void ItemSlot::Init()
{
	slot.setSize({ 40,70 });
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
		//FIX : 인벤토리 단계에서 처리해주기
		if (InputMgr::GetMouseButtonDown(sf::Mouse::Left)) {
			if (item != nullptr) {
				item->DragItem();
				dragItem = item;
				item = nullptr;
			}
		}
		if (InputMgr::GetMouseButtonUp(sf::Mouse::Left)) {
			if (dragItem != nullptr) {
				SetItem(dragItem);
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
	if (item != nullptr) {
		item->Draw(window);
	}
}

void ItemSlot::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	slot.setPosition(pos);
}

void ItemSlot::SetItem(Item* item)
{
	this->item = item;

	sf::FloatRect bound = slot.getLocalBounds();
	item->SetPosition({ bound.width / 2 + slot.getPosition().x ,bound.height / 2 + slot.getPosition().y });
}
