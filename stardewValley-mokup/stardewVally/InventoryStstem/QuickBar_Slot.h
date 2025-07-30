#pragma once
#include "GameObject.h"
#include "InUIItem.h"

class QuickBar_Slot : public GameObject
{
private:
	sf::RectangleShape slot;
	std::string texId;

	InUIItem* item = nullptr;
	InUIItem copyItem;
public:
	QuickBar_Slot(const std::string& texId="", const std::string& name = "");
	~QuickBar_Slot() override = default;

	// GameObject을(를) 통해 상속됨
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetItem(InUIItem* item);
	Item* GetItem() { return item; };
};

