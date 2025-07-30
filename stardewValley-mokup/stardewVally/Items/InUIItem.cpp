#include "stdafx.h"
#include "InUIItem.h"

InUIItem::InUIItem(ItemInfo type)
	:Item(type, true)
{
	
}

void InUIItem::Reset()
{
	Item::Reset();
	quantityText.setFont(FONT_MGR.Get("fonts/DOSGothic.ttf"));

	quantityText.setFillColor(sf::Color::Black);
	quantityText.setString(std::to_string(quantity));
	Utils::SetOrigin(quantityText, Origins::BR);

	quantityText.setPosition({ GetPosition().x + 25.f , GetPosition().y + 15.f });
}

void InUIItem::Update(float dt)
{
	if (isDrag) {
		SetPosition((sf::Vector2f)InputMgr::GetMouseUIRect().getPosition());
	}
}

void InUIItem::Draw(sf::RenderWindow& window)
{
	Item::Draw(window);
	if (!isDrag) {
		window.draw(quantityText);
	}
}

void InUIItem::DragItem(bool isDrag)
{
	this->isDrag = isDrag;
}

void InUIItem::PlusQuantity(int quantity)
{
	Item::PlusQuantity(quantity);
	UseItem();
}

bool InUIItem::UseItem()
{
	quantityText.setString(std::to_string(quantity));
	Utils::SetOrigin(quantityText, Origins::BR);
	return true;
}

