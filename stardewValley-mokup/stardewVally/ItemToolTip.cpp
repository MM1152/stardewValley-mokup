#include "stdafx.h"
#include "ItemToolTip.h"
#include "Item.h"
ItemToolTip::ItemToolTip(const std::string name)
	:GameObject(name)
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 10;
}

void ItemToolTip::Init()
{
}

void ItemToolTip::Release()
{
}

void ItemToolTip::Reset()
{
	TEXTURE_MGR.Load(GRAPHICS_PATH"inventory_bg.png");
	FONT_MGR.Load(FONT_PATH"Stardew_Valley.ttf");

	toolTipTop.setTexture(TEXTURE_MGR.Get(GRAPHICS_PATH"inventory_bg.png"));
	toolTipTop.setScale(0.2f , 0.3f);
	toolTipBottom.setTexture(TEXTURE_MGR.Get(GRAPHICS_PATH"inventory_bg.png"));
	toolTipBottom.setScale(0.2f, 0.8f);
	textTop.setFont(FONT_MGR.Get(FONT_PATH"Stardew_Valley.ttf"));
	textBottom.setFont(FONT_MGR.Get(FONT_PATH"Stardew_Valley.ttf"));

	toolTipBottom.setPosition({ toolTipTop.getPosition().x , (toolTipTop.getLocalBounds().height * toolTipTop.getScale().y) + toolTipTop.getPosition().y });

	textTop.setFillColor(sf::Color::Black);
	textBottom.setFillColor(sf::Color::Black);
}

void ItemToolTip::Update(float dt)
{
	if (info) {
		toolTipTop.setPosition((sf::Vector2f)InputMgr::GetMousePosition() + toolTipPadding );
		toolTipBottom.setPosition({ (float)InputMgr::GetMousePosition().x + toolTipPadding.x,(float)InputMgr::GetMousePosition().y + (toolTipTop.getLocalBounds().height * toolTipTop.getScale().y) + toolTipPadding.y });

		textTop.setPosition(toolTipTop.getPosition() + textPadding);
		textBottom.setPosition(toolTipBottom.getPosition() + textPadding);
	}
}

void ItemToolTip::Draw(sf::RenderWindow& window)
{
	if (info) {
		window.draw(toolTipTop);
		window.draw(toolTipBottom);
		window.draw(textTop);
		window.draw(textBottom);
	}
}

void ItemToolTip::SetItemInfo(Item* info)
{
	if (!info) {
		this->info = nullptr;
		return;
	}

	this->info = info->GetItemInfo();
	SetString(textTop , this->info->itemName);
}

void ItemToolTip::SetString(sf::Text& text, const std::string& word)
{
	text.setString(word);
}