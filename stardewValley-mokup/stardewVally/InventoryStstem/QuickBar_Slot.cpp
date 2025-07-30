#include "stdafx.h"
#include "QuickBar_Slot.h"
#include "Item.h"
QuickBar_Slot::QuickBar_Slot(const std::string& texId, const std::string& name)
	:GameObject(name)
	,texId(texId)
{
}

void QuickBar_Slot::Init()
{
	slot.setSize({ 65,65 });
	copyItem.Init();
}

void QuickBar_Slot::Release()
{
}

void QuickBar_Slot::Reset()
{
	slot.setTexture(&TEXTURE_MGR.Get(texId));
}

void QuickBar_Slot::Update(float dt)
{
	if (item) {
		if (item && item->GetQuantity() <= 0) {
			item->SetItemInfo(nullptr);
			item = nullptr;
		}
		SetItem(item);
	}
}

void QuickBar_Slot::Draw(sf::RenderWindow& window)
{
	window.draw(slot);
	if (item != nullptr) {
		copyItem.Draw(window);
	}

}

void QuickBar_Slot::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	slot.setPosition(pos);
}

void QuickBar_Slot::SetItem(InUIItem* item)
{
	this->item = item;
	if (!item) {
		return ;
	}

	copyItem = *item;
	copyItem.SetPosition({ GetPosition().x + slot.getSize().x / 2 , GetPosition().y + slot.getSize().y / 2 });
	copyItem.SetItemInfo(item);
}

