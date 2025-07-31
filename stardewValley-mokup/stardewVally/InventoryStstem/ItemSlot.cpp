#include "stdafx.h"
#include "ItemSlot.h"
#include "Item.h"
#include "SellBox.h"

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
	if (item) {
		item->Reset();
	}
}

void ItemSlot::Update(float dt)
{
    if (item && item->GetQuantity() <= 0) {
        delete item;
        item = nullptr;
    }

    bool isMouseOverSlot = slot.getGlobalBounds().intersects(InputMgr::GetMouseUIRect());
    slot.setFillColor(isMouseOverSlot ? sf::Color(187, 187, 187) : sf::Color::White);
	
    if (!isMouseOverSlot) {
        onMouse = false;
        return;
    }


    onMouse = true;

    if (InputMgr::GetMouseButtonDown(sf::Mouse::Left)) {
        if (sellBox && sellBox->IsBoxOpen() && item && !dragItem) 
        {
            sellBox->SellItem(*item);
            delete item;
            item = nullptr;
            return;
        }
        if (!dragItem && item && sellBox->IsBoxClosed()) 
        {
            item->DragItem(true);
            dragItem = item;
            item = nullptr;
            return;
        }
        if (dragItem) {
            if (item) {
                InUIItem* temp = item;
                SetItem(dragItem);    
                dragItem->DragItem(false);
                dragItem = temp;        
                dragItem->DragItem(true);
            }
            else {
                SetItem(dragItem);
                dragItem->DragItem(false);
                dragItem = nullptr;
            }
        }
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

void ItemSlot::SetSellBox(SellBox* sb)
{
    sellBox = sb;
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
