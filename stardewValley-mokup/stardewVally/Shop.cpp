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
	sprite.setPosition(pos);
}

void Shop::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	sprite.setRotation(rot);
}

void Shop::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	sprite.setScale(s);
}

void Shop::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	sprite.setOrigin(o);
}

void Shop::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(sprite, preset);
	}
}

void Shop::Init()
{
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
	SetPosition({ -500.f, 0.f });

	const std::vector<ItemInfo>& items = itemDataMgr::Instance().GetItem("Pierre's General Store");
	CreateItemSlots(items);
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
