#include "stdafx.h"
#include "Shop.h"
#include "itemDataMgr.h"
#include "Item.h"

Shop::Shop(const std::string& name)
	: GameObject(name)
{
}

void Shop::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	backgroundSprite.setPosition(pos);
}

void Shop::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	backgroundSprite.setRotation(rot);
}

void Shop::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	backgroundSprite.setScale(s);
}

void Shop::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	backgroundSprite.setOrigin(o);
}

void Shop::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(backgroundSprite, preset);
	}
}

void Shop::Init()
{
	backgroundSprite.setTexture(TEXTURE_MGR.Get("graphics/shop_bg.png"));
	backgroundSprite.setPosition({200.f, 100.f});

	sf::Font& font = FONT_MGR.Get("fonts/main_font.tff");

	itemNameText.setFont(font);
	itemNameText.setCharacterSize(18);
	itemNameText.setFillColor(sf::Color::White);

	itemDescText.setFont(font);
	itemDescText.setCharacterSize(14);
	itemDescText.setFillColor(sf::Color(200, 200, 200));

	itemPriceText.setFont(font);
	itemPriceText.setCharacterSize(16);
	itemPriceText.setFillColor(sf::Color::Yellow);
	
}

void Shop::Release()
{

}

void Shop::Reset()
{

}

void Shop::Update(float dt)
{
}

void Shop::Draw(sf::RenderWindow& window)
{
	if (!isUiShow)
		return;

	for (ItemSlot* slot : itemSlots)
	{
		slot->Draw(window);
	}
}

void Shop::ShowUi()
{
	isUiShow = true;
	SetPosition({ 200.f, 100.f }); 

	const std::vector<ItemInfo>& items = itemDataMgr::Instance().GetItem("Pierre's General Store");
	CreateItemSlots(items);

	itemNameText.setPosition({ GetPosition().x + 400.f, GetPosition().y + 50.f });
	itemDescText.setPosition({ GetPosition().x + 400.f, GetPosition().y + 80.f });
	itemPriceText.setPosition({ GetPosition().x + 400.f, GetPosition().y + 140.f });
}

void Shop::CloseUi()
{
	isUiShow = false;
}

bool Shop::isUiShowing()
{
	return isUiShow;
}

void Shop::CreateItemSlots(const std::vector<ItemInfo>& items)
{
	for (ItemSlot* slot : itemSlots)
	{
		delete slot;
	}
	itemSlots.clear();

	float x = GetPosition().x + 50.f;
	float y = GetPosition().y + 50.f;
	float spacingY = 80.f;

	for (int i = 0; i < items.size(); ++i)
	{
		const ItemInfo& info = items[i];

		Item* item = new Item(info);
		item->Init();
		item->Reset();

		ItemSlot* slot = new ItemSlot(info.itemTextureId, info.itemName);
		slot->Init();
		slot->Reset();
		slot->SetPosition({ x,y + i * spacingY });

		slot->SetItem(item);

		itemSlots.push_back(slot);
	}
}
