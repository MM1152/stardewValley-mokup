#pragma once
#include "GameObject.h"
#include "itemDataMgr.h"

class Inventory;
class Button;
class Shop : public GameObject
{
protected:
    sf::Sprite backgroundSprite;
    sf::Sprite portraitBox;
    sf::Sprite portraitShop;
    sf::Sprite itemSlot_bg;

    bool isUiShow = false;
   

    std::vector<ItemInfo> shopItems;

    std::vector<sf::Sprite> itemSprites;
    std::vector<sf::Text> itemNameTexts;
    std::vector<sf::Text> itemDescTexts;
    std::vector<sf::Text> itemPriceTexts;

    sf::Font font;

    Inventory* inventory = nullptr;

    std::vector<Button*> buyButtons;

public:
    Shop(const std::string& name);
    void SetPosition(const sf::Vector2f& pos) override;
    void SetRotation(float rot) override;
    void SetScale(const sf::Vector2f& s) override;
    void SetOrigin(const sf::Vector2f& o) override;
    void SetOrigin(Origins preset) override;

    void Init() override;
    void Reset() override;
    void Release() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;

    void ShowUi();
    void CloseUi();
    bool isUiShowing();
    void SetInventory(Inventory* inv) { inventory = inv; }

private:
    void LoadShopItems(const std::vector<ItemInfo>& items);

};

