#pragma once
#include "GameObject.h"

class Item;
class ItemToolTip : public GameObject
{
private:
	sf::Sprite toolTipTop;
	sf::Sprite toolTipBottom;

	sf::Text textTop;
	sf::Text textBottom;

	ItemInfo* info;
	
	sf::Vector2f toolTipPadding = { 20.f , 20.f };
	sf::Vector2f textPadding = { 10.f , 10.f };
	void SetString(sf::Text& text , const std::string& word);

public:
	ItemToolTip(const std::string name = "");
	~ItemToolTip() override = default;

	// GameObject을(를) 통해 상속됨
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetItemInfo(Item* info);
};

