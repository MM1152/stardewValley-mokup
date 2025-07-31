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
	bool onMouse = false;
	SellBox* sellBox = nullptr;

public:
	static InUIItem* dragItem;

	ItemSlot(const std::string& texId = "", const std::string& fontId = "", const std::string& name = "");
	~ItemSlot() override = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetPosition(const sf::Vector2f& pos) override;
	InUIItem* GetItem() { return item; };
	bool GetOnMouse() { return onMouse; };
	virtual bool SetItem(InUIItem* item);
	bool IsSetting() { return item; };
	void RemoveItem() { item = nullptr; };
	void SetSellBox(SellBox* sb);
};

