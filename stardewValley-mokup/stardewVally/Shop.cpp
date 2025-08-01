#include "stdafx.h"
#include "Shop.h"
#include "itemDataMgr.h"
#include "Item.h"
#include "Inventory.h"
#include "Button.h"
#include "Player.h"
#include "TimeMoneyUi.h"
#include "ItemToolTip.h"

Shop::Shop(const std::string& name)
	: GameObject(name)
{
    sortingLayer = SortingLayers::UI;
    sortingOrder = 1;
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
    toolTip = new ItemToolTip();
    toolTip->Init();
}

void Shop::Release()
{

}

void Shop::Reset()
{
    backgroundSprite.setTexture(TEXTURE_MGR.Get("graphics/shop_bg.png"));
    backgroundSprite.setPosition({FRAMEWORK.GetWindowSizeF().x * 0.5f + 100 , FRAMEWORK.GetWindowSizeF().y * 0.5f + 100});
    backgroundSprite.setScale({0.8, 0.8f});
    Utils::SetOrigin(backgroundSprite, Origins::MC);

    sf::Vector2f bgScale = backgroundSprite.getScale();

    portraitBox.setTexture(TEXTURE_MGR.Get("graphics/portraitsBox.png"));
    portraitBox.setPosition({backgroundSprite.getPosition().x - 400,backgroundSprite.getPosition().y - 23});
    Utils::SetOrigin(portraitBox, Origins::MC);
    portraitBox.setScale({ 1.4f * bgScale.x, 1.4f * bgScale.y });

    portraitShop.setTexture(TEXTURE_MGR.Get("graphics/Pierre.png"));
    portraitShop.setPosition({ backgroundSprite.getPosition().x - 400.f,backgroundSprite.getPosition().y - 21.f });
    Utils::SetOrigin(portraitShop, Origins::MC);
    portraitShop.setScale({ 2.9f * bgScale.x, 2.9f * bgScale.y });

    itemSlot_bg.setTexture(TEXTURE_MGR.Get("graphics/itemSlot_bg.png"));

    font = FONT_MGR.Get("fonts/Stardew_Valley.ttf");
    toolTip->Reset();
}

void Shop::Update(float dt) 
{
    if (!isUiShow)
        return;

    for (auto btn : buyButtons)
        btn->Update(dt);

    toolTip->Update(dt);
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

	const std::vector<ItemInfo>& items = itemDataMgr::Instance().GetShopItemList("Pierre's General Store");
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
    for (auto btn : buyButtons)
    {
        delete btn;
    }

    buyButtons.clear();

    shopItems = items;

    itemSprites.clear();
    itemNameTexts.clear();
    itemDescTexts.clear();
    itemPriceTexts.clear();

    font = FONT_MGR.Get("fonts/Stardew_Valley.ttf");

    sf::Vector2f bgPos = backgroundSprite.getPosition();
    sf::Vector2f bgScale = backgroundSprite.getScale();

    float x = bgPos.x - 230.f * bgScale.x;
    float y = bgPos.y - 105.f * bgScale.y;
    float spacingY = 60.f * bgScale.y;

    for (int i = 0; i < items.size(); ++i)
    {
        const ItemInfo& info = items[i];

        Button* btn = new Button("fonts/Stardew_Valley.ttf", "graphics/itemSlot_bg.png", "BuyButton_" + std::to_string(i));
        btn->Init();
        btn->SetPosition({ x - 130.f * bgScale.x, y + i * spacingY - 30.f * bgScale.y });
        btn->SetString("                                ");
        btn->SetScale({ 1.5f * bgScale.x, 2.0f * bgScale.y });
        btn->Reset();  

        sf::Sprite sprite;
        sprite.setTexture(TEXTURE_MGR.Get(info.itemTextureId));
        sprite.setScale({ 2.8f * bgScale.x, 2.5f * bgScale.y });
        sprite.setPosition(x - 112.f * bgScale.x, y + i * spacingY - 20.f * bgScale.y);
        itemSprites.push_back(sprite);
   
        sf::Text nameText;
        nameText.setFont(font);
        nameText.setString(info.itemName);
        nameText.setCharacterSize(static_cast<unsigned int>(40 * bgScale.y));
        nameText.setFillColor(sf::Color::Black);
        nameText.setPosition(x - 50.f * bgScale.x, y + i * spacingY - 30.f * bgScale.y);
        itemNameTexts.push_back(nameText);

        sf::Text priceText;
        priceText.setFont(font);
        priceText.setString(std::to_string(info.price));
        priceText.setCharacterSize(static_cast<unsigned int>(32 * bgScale.y));
        priceText.setFillColor(sf::Color::Black);
        priceText.setPosition(x + 420.f * bgScale.x, y + i * spacingY - 24.f * bgScale.y);
        itemPriceTexts.push_back(priceText);

        btn->onClickFunc = [this, i]() {
            const ItemInfo& item = shopItems[i];
            if (inventory && player)
            {
                int price = item.price;
                int currentMoney = player->GetMoney();

                if (currentMoney >= price)
                {
                    bool success = inventory->AddItem(item);
                    if (success)
                    {
                        player->SetMoney(currentMoney - price);
                        timeMoneyUi->SettingMoney(player->GetMoney());
                        std::cout << "item added " << item.itemName << std::endl;
                    }
                    else
                    {
                        std::cout << "inventory is full" << std::endl;
                    }
                }
                else
                {
                    std::cout << "Not enough money" << std::endl;
                }
            }
            };

        buyButtons.push_back(btn);
    }
}


