#pragma once
#include "GameObject.h"
#include "InUIItem.h"

class ItemSlot : public GameObject
{
private:
	std::string texId;
	sf::RectangleShape slot;
	
	InUIItem* item = nullptr;
public:
	static InUIItem* dragItem;

	ItemSlot(const std::string& texId = "", const std::string& name = "");
	~ItemSlot() override = default;

	// GameObject��(��) ���� ��ӵ�
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
};

