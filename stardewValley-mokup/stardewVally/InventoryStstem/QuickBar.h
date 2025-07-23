#pragma once
#include "GameObject.h"
#include "Inventory.h"
#include "ItemSlot.h"
class QuickBar : public GameObject
{
private:
	std::string texId;
	sf::RectangleShape quickBar;
	sf::RectangleShape outLine;
	std::vector<ItemSlot*> quickBar_Slots;
	
public:
	QuickBar(const std::string& texId = "" , const std::string& name = "");
	~QuickBar() override = default;

	// GameObject��(��) ���� ��ӵ�
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

