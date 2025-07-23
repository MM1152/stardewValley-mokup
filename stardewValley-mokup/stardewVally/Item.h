#pragma once
#include "GameObject.h"

class ItemSlot;
class Item : public GameObject
{
private:
	sf::Sprite sp;
	std::string texId;

	sf::CircleShape testItemImage;

	bool isDrag = false;
public:
	bool isSetting = true;

	Item(const std::string& texId = "" , const std::string& name = "");
	~Item() override = default;

	// GameObject을(를) 통해 상속됨
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetPosition(const sf::Vector2f& pos) override;

	void DragItem();
	bool GetDrag() { return isDrag; };
	
};

