#include "stdafx.h"
#include "Shop.h"
#include "itemDataMgr.h"
#include "Item.h"
#include "Inventory.h"
#include "Button.h"

Shop::Shop(const std::string& name)
	: GameObject(name)
{
    sortingLayer = SortingLayers::UI;
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
    backgroundSprite.setPosition({FRAMEWORK.GetWindowSizeF().x / 2 , FRAMEWORK.GetWindowSizeF().y / 2});
    backgroundSprite.setScale({0.7f, 0.8f});

    portraitBox.setTexture(TEXTURE_MGR.Get("graphics/portraitsBox.png"));
    portraitBox.setPosition({backgroundSprite.getPosition().x - 160,backgroundSprite.getPosition().y});
    portraitBox.setScale({ 0.9f,0.9f });

    portraitShop.setTexture(TEXTURE_MGR.Get("graphics/Pierre.png"));
    portraitShop.setPosition({ backgroundSprite.getPosition().x - 150.f,backgroundSprite.getPosition().y + 10.f });
    portraitShop.setScale({ 2.0f,2.0f });

    itemSlot_bg.setTexture(TEXTURE_MGR.Get("graphics/itemSlot_bg.png"));

    font = FONT_MGR.Get("fonts/Stardew_Valley.ttf");
}

void Shop::Update(float dt) 
{
    if (!isUiShow)
        return;

    for (auto btn : buyButtons)
        btn->Update(dt);
}

void Shop::Draw(sf::RenderWindow& window)
{
    if (!isUiShow)
        return;

    window.draw(backgroundSprite);
    window.draw(portraitBox);
    window.draw(portraitShop);

    for (auto btn : buyButtons)
    {
        btn->Draw(window);
    }

    for (size_t i = 0; i < shopItems.size(); ++i)
    {
        window.draw(itemSprites[i]);
        window.draw(itemNameTexts[i]);
     /*   window.draw(itemDescTexts[i]);*/
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

    float x = backgroundSprite.getPosition().x + 30.f;
    float y = backgroundSprite.getPosition().y + 10.f;
    float spacingY = 50.f;

    for (int i = 0; i < items.size(); ++i)
    {
        const ItemInfo& info = items[i];

        Button* btn = new Button("fonts/Stardew_Valley.ttf", "graphics/itemSlot_bg.png", "BuyButton_" + std::to_string(i));
        btn->Init();
        btn->SetPosition({ x - 20, y + i * spacingY + 5.f});
        btn->SetString("                      ");
        btn->SetScale({1.5f, 1.6f});
        btn->Reset();  

        btn->onClickFunc = [this, i]() {
            const ItemInfo& item = shopItems[i];
            if (inventory)
            {
                bool success = inventory->AddItem(item);
                if (success)
                {
                    std::cout << "item added " << item.itemName << std::endl;
                }
                else
                {
                    std::cout << "inventory is full" << std::endl;
                }
            }
            };

        buyButtons.push_back(btn);

        sf::Sprite sprite;
        sprite.setTexture(TEXTURE_MGR.Get(info.itemTextureId));
        sprite.setScale({2.2f,2.2f});
        sprite.setPosition(x - 10.f, y + i * spacingY + 10.f);
        itemSprites.push_back(sprite);
   
        sf::Text nameText;
        nameText.setFont(font);
        nameText.setString(info.itemName);
        nameText.setCharacterSize(30);
        nameText.setFillColor(sf::Color::Black);
        nameText.setPosition(x + 40.f, y + i * spacingY + 10.f);
        itemNameTexts.push_back(nameText);

 /*       sf::Text descText;
        descText.setFont(font);
        descText.setString(info.itemDes);
        descText.setCharacterSize(14);
        descText.setFillColor(sf::Color::Black);
        descText.setPosition(x + 50.f, y + i * spacingY + 20);
        itemDescTexts.push_back(descText);*/

        sf::Text priceText;
        priceText.setFont(font);
        priceText.setString(std::to_string(info.price));
        priceText.setCharacterSize(22);
        priceText.setFillColor(sf::Color::Black);
        priceText.setPosition(x + 420.f, y + i * spacingY + 15);
        itemPriceTexts.push_back(priceText);
    }
}


