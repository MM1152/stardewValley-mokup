#pragma once
#include "GameObject.h"
#include "ItemSlot.h"
#include "QuickBar_Slot.h"

class InUIItem;
class QuickBar : public GameObject
{
private:
	std::string texId;
	sf::RectangleShape quickBar;
	sf::RectangleShape outLine;
	std::vector<QuickBar_Slot*> quickBar_Slots;		

	int idx = 0;
public:
	QuickBar(const std::string& texId = "" , const std::string& name = "");
	~QuickBar() override = default;

	// GameObject을(를) 통해 상속됨
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetItem(InUIItem* item , int idx);
	Item* GetItem();
	int GetQuickBarIdx() { return idx; };
};

