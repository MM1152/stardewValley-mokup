#include "stdafx.h"
#include "Shop.h"
#include "itemDataMgr.h"
#include "Item.h"
#include "Inventory.h"

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

}

void Shop::Release()
{

}

void Shop::Reset()
{
    backgroundSprite.setTexture(TEXTURE_MGR.Get("graphics/shop_bg.png"));
    backgroundSprite.setPosition({ -160.f, -150.f });
    backgroundSprite.setScale({3.f, 3.f});

    font = FONT_MGR.Get("fonts/Stardew_Valley.ttf");
}

void Shop::Update(float dt)
{
}

void Shop::Draw(sf::RenderWindow& window)
{
    if (!isUiShow)
        return;

    window.draw(backgroundSprite);

    for (size_t i = 0; i < shopItems.size(); ++i)
    {
        window.draw(itemSprites[i]);
        window.draw(itemNameTexts[i]);
        window.draw(itemDescTexts[i]);
        window.draw(itemPriceTexts[i]);
    }
}

void Shop::ShowUi()
{
    isUiShow = true;

	const std::vector<ItemInfo>& items = itemDataMgr::Instance().GetItem("Pierre's General Store");
	LoadShopItems(items);
}

void Shop::CloseUi()
{
	isUiShow = false;
}

bool Shop::isUiShowing()
{
	return isUiShow;
}

void Shop::LoadShopItems(const std::vector<ItemInfo>& items)
{
    shopItems = items;

    itemSprites.clear();
    itemNameTexts.clear();
    itemDescTexts.clear();
    itemPriceTexts.clear();

    font = FONT_MGR.Get("fonts/Stardew_Valley.ttf");

    float x = GetPosition().x-100;
    float y = GetPosition().y - 100;
    float spacingY = 90.f;

    for (int i = 0; i < items.size(); ++i)
    {
        const ItemInfo& info = items[i];

        sf::Sprite sprite;
        sprite.setTexture(TEXTURE_MGR.Get(info.itemTextureId));
        sprite.setScale({2.5f,2.5f});
        sprite.setPosition(x, y + i * spacingY);
        itemSprites.push_back(sprite);

        sf::Text nameText;
        nameText.setFont(font);
        nameText.setString(info.itemName);
        nameText.setCharacterSize(18);
        nameText.setFillColor(sf::Color::Black);
        nameText.setPosition(x + 70.f, y + i * spacingY);
        itemNameTexts.push_back(nameText);

        sf::Text descText;
        descText.setFont(font);
        descText.setString(info.itemDes);
        descText.setCharacterSize(14);
        descText.setFillColor(sf::Color::Black);
        descText.setPosition(x + 70.f, y + i * spacingY + 24.f);
        itemDescTexts.push_back(descText);

        sf::Text priceText;
        priceText.setFont(font);
        priceText.setString("price: " + std::to_string(info.price));
        priceText.setCharacterSize(16);
        priceText.setFillColor(sf::Color::Black);
        priceText.setPosition(x + 70.f, y + i * spacingY + 48.f);
        itemPriceTexts.push_back(priceText);
    }
}


