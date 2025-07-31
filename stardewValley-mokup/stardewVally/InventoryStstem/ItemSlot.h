#pragma once
#include "GameObject.h"
#include "InUIItem.h"

class SellBox;
class ItemSlot : public GameObject
{
private:
	std::string texId;
	std::string fontId;

	sf::RectangleShape slot;

	InUIItem* item = nullptr;
	SellBox* sellBox = nullptr;

public:
	static InUIItem* dragItem;

	ItemSlot(const std::string& texId = "", const std::string& fontId = "", const std::string& name = "");
	~ItemSlot() override = default;

	// GameObject을(를) 통해 상속됨
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetPosition(const sf::Vector2f& pos) override;
	virtual bool SetItem(InUIItem* item);
	InUIItem* GetItem() { return item; };
	bool IsSetting() { return item; };
	void RemoveItem() { item = nullptr; };
	void SetSellBox(SellBox* sb);
};

