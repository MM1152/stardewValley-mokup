#pragma once
#include "GameObject.h"

class Item;
class ItemSlot : public GameObject
{
private:
	std::string texId;
	sf::RectangleShape slot;
	
	
	Item* item = nullptr;
	bool startDragSlot;
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
	void SetItem(Item* item);
	bool IsSetting() { return item; };
	void RemoveItem() { item = nullptr; };
};

