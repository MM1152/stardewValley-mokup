#pragma once
#include "GameObject.h"

class Item;
class ItemSlot : public GameObject
{
private:
	std::string texId;
	sf::RectangleShape slot;
	
	Item* item = nullptr;
public:
	static Item* dragItem;

	ItemSlot(const std::string& texId = "", const std::string& name = "");
	~ItemSlot() override = default;

	// GameObject을(를) 통해 상속됨
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetPosition(const sf::Vector2f& pos) override;
	virtual bool SetItem(Item* item);
	Item* GetItem() { return item; };
	bool IsSetting() { return item; };
	void RemoveItem() { item = nullptr; };
};

